#include "Map.hpp"
#include <iostream>

Map::Map(std::string input_file) {
  if (map.loadFromFile(input_file) == false) {
    std::cout << "Fichier donné non existant" << std::endl;
    throw;
  }
  map_texture.loadFromImage(map);
  size = map.getSize();

  collide_map.resize(size.x * size.y);
  normals.resize(size.x * size.y);

  updateColliders();
}

void Map::updateColliders() {
  constexpr int MASK_SIZE = 5;
  bool solidN, nonSolidN, valid;
  std::vector<bool> mask = {false, true, false,
                            true, false, true,
                            false, true, false};
  float dist;

  for (int i = 0; i < int(size.x); i++) {
    for (int j = 0; j < int(size.y); j++) {
      solidN = false;
      nonSolidN = false;
      // détermine si le pixel examiné est solide
      collide_map[coordsToPix(i, j)] = (map.getPixel(i, j).a == 0);

      // détermine si le pixel examiné peut posséder une normale
      if (collide_map[coordsToPix(i, j)] == true) {
        // un pixel possède une normale que s'il est solide
        // et s'il est entouré de pixels solides ET non-solides
        for (int u = i-1; u <= i+1; i++) {
          for (int v = j-1; v <= j+1; j++) {
            valid = (u >= 0 && v >= 0 && u < size.x && v < size.y);
            if (valid && mask[coordsToPix(u-i+1, v-j+1)] == true){
              if (map.getPixel(u, v).a == 0) {
                nonSolidN = true;
              }
              else {
                solidN = true;
              }
            } // tests de validité
          }
        }
      }

      // calcul de la normale
      // https://gamedevelopment.tutsplus.com/tutorials/coding-destructible-pixel-terrain-how-to-make-everything-explode--gamedev-45
      if (solidN && nonSolidN) {
      	sf::Vector2f normal;

        for (int u = i-STEP; u <= i+STEP; i++) {
          for (int v = j-STEP; v <= j+STEP; j++) {
            valid = (u >= 0 && v >= 0 && u < size.x && v < size.y);
            if (valid && map.getPixel(u, v).a != 0) {
              normal.x -= u;
              normal.y -= v;
            }
          }
        }
        dist = std::sqrt(normal.x * normal.x + normal.y * normal.y);
        normals[coordsToPix(i, j)] = normal/dist;
      }
    }
  }
}
