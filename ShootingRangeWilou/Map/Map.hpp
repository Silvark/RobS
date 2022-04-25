#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>

class Map : public sf::Drawable { // permet d'avoir un objet customisé et pouvant être dessiné
  private:
    sf::Image map; // tous les calculs de modification de terrain se font sur l'image..
    sf::Texture map_texture; // car on peut pas manipuler les pixels individuels d'un sf::Texture
    sf::Vector2u size; // getSize() renvoie un Vector2u

    // TODO : envisager de faire des classes CollideMap & Normals ?
    std::vector<bool> collide_map; // (1) : collisions "pixel-perfect" requièrent un array de booléens
    std::vector<sf::Vector2f> normals; // (2) : vecteur de vecteurs normaux

    /*
    (1) : https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Texture.php
    (2) : https://gamedevelopment.tutsplus.com/tutorials/coding-destructible-pixel-terrain-how-to-make-everything-explode--gamedev-45
    */

    size_t coordsToPix(int x, int y) const {return y * size.x + x;}
    void updateColliders();  // update collide_map & normals en fonction de l'état de map

  public:
    Terrain(std::string input_file); // constructeur
    sf::Vector2f getNormal(int x, int y) const;
};

#endif
