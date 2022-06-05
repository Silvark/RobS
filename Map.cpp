#include "Map.hpp"
#include <iostream>
#include <cmath>

Map::Map(std::string input_file) {
  if (map.loadFromFile(input_file) == false) {
    std::cout << "Fichier donné non existant" << std::endl;
    throw;
  }
  map_texture.loadFromImage(map);
  size = map.getSize();

  collide_map.resize(size.x * size.y);
  normals.resize(size.x * size.y);
  updateMap(0, 0, size.x, size.y);
}

size_t Map::coordsToPix(int x, int y) const {
  if (y < 0 || x < 0 || x > size.x || y > size.y) {
    throw std::invalid_argument( "[ERROR] Accès terrain invalide" );
  }
  return y * size.x + x;
}

void Map::setPixel(int x, int y, int value) {
  collide_map[coordsToPix(x, y)] = value;
  if (value) {
    // cas 1 : construction
    map.setPixel(x, y, sf::Color(128, 128, 128, 255));
  }
  else {
    // cas 2 : destruction
    map.setPixel(x, y, sf::Color::Transparent);
  }
}

void Map::updateMap(int left, int top, int width, int height) {
  map_texture.loadFromImage(map);
  updateCollideMap(left, top, width, height);
  updateNormals(left, top, width, height);
}

void Map::updateCollideMap(int left, int top, int width, int height) {
  for (int i = left; i < int(left + width); i++) {
    for (int j = top; j < int(top + height); j++) {
      // détermine si le pixel examiné est solide
      collide_map[coordsToPix(i, j)] = (map.getPixel(i, j).a != 0);
    }
  }
}

void Map::updateNormals(int left, int top, int width, int height) {
  constexpr int MASK_SIZE = 5;
  for (int i = left; i < int(left + width); i++) {
    for (int j = top; j < int(top + height); j++) {

      if (checkSurfaceValidity(i, j) && collide_map[coordsToPix(i, j)]) {
        normals[coordsToPix(i, j)] = computeNormal(i, j, MASK_SIZE);
        // map.setPixel(i, j, sf::Color(255, 0, 0, 128)); // debug
      }

    }
  }
}

bool Map::checkSurfaceValidity(int x, int y) {
  // un pixel possède une normale que s'il est solide
  // et s'il est voisin d'un pixel non solide
	bool nonSolidN = false;
  bool indexValidity = false;
  bool mask_target = false;
  std::vector<bool> mask = {false, true, false,
                            true, false, true,
                            false, true, false};

  for (int i = x-1; i <= x+1; i++) {
    for (int j = y-1; j <= y+1; j++) {
      indexValidity = (i > 0 && j > 0 && i < int(size.x) && j < int(size.y));
      mask_target = mask[((j - y + 1) * 3) + (i - x + 1)];
      if (indexValidity && mask_target) {
        if (!collide_map[coordsToPix(i, j)]) {
          nonSolidN = true;
        }
      }
    }
  }
  return (nonSolidN);
}

sf::Vector2f Map::computeNormal(int x, int y, int mask_size) {
  // calcul de la normale
  // https://gamedevelopment.tutsplus.com/tutorials/coding-destructible-pixel-terrain-how-to-make-everything-explode--gamedev-45
  sf::Vector2f normal(0, 0);
  float dist;
  bool valid;
  for (int u = x-mask_size; u <= x+mask_size; u++) {
    for (int v = y-mask_size; v <= y+mask_size; v++) {
      valid = (u >= 0 && v >= 0 && u < int(size.x) && v < int(size.y));
      if (valid && map.getPixel(u, v).a != 0) {
        normal.x -= u-x;
        normal.y -= v-y;
      }
    }
  }
  dist = std::sqrt(normal.x * normal.x + normal.y * normal.y);
  return normal/dist;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite map_sprite(map_texture);
	target.draw(map_sprite, states);
  // drawNormals(target); // debug
}
