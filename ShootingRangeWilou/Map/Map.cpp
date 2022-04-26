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
  updateMap();
}

void Map::updateMap() {
  updateCollideMap();
  updateNormals();
}

void Map::updateCollideMap() {
  for (int i = 0; i < int(size.x); i++) {
    for (int j = 0; j < int(size.y); j++) {
      // détermine si le pixel examiné est solide
      collide_map[coordsToPix(i, j)] = (map.getPixel(i, j).a != 0);
    }
  }
}

void Map::updateNormals() {
  constexpr int MASK_SIZE = 5;
  for (int i = 0; i < int(size.x); i++) {
    for (int j = 0; j < int(size.y); j++) {

      if (checkSurfaceValidity(i, j)) {
        normals[coordsToPix(i, j)] = computeNormal(i, j, MASK_SIZE);
        map.setPixel(i, j, sf::Color::Red); // debug
      }

    }
  }
  map_texture.loadFromImage(map); // debug
}

bool Map::checkSurfaceValidity(int x, int y) {
  // un pixel possède une normale que s'il est solide
  // et s'il est entouré de pixels solides ET non-solides
  bool solidN = false;
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
        if (collide_map[coordsToPix(i, j)]) {
          solidN = true;
        }
        else {
          nonSolidN = true;
        }
      }
    }
  }
  return (solidN && nonSolidN);
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
  drawNormals(target);
}
