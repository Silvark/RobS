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

    void updateCollideMap(int left, int top, int width, int height);
    void updateNormals(int left, int top, int width, int height);
    bool checkSurfaceValidity(int x, int y);
    sf::Vector2f computeNormal(int x, int y, int mask_size);

  public:
    Map(std::string input_file); // constructeur
    size_t coordsToPix(int x, int y) const {return y * size.x + x;}

    sf::Vector2f getNormal(int x, int y) const;

    sf::Vector2u getSize() const {return size;}

    bool getPixel(int x, int y) const {return collide_map[coordsToPix(x, y)];}
    void setPixel(int x, int y, int value);

    void updateMap(int left, int top, int width, int height);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // debug
    void drawNormals(sf::RenderTarget& target) const {
    	constexpr float LEN = 20;
    	for (unsigned x = 0; x < size.x; x++) {
    		for (unsigned y = 0; y < size.y; y++) {
    			// Ensure this is a surface point

    			if (collide_map[coordsToPix(x, y)]) {
    				sf::Vertex line[2];
    				line[0].position = sf::Vector2f(x, y);
    				line[0].color = sf::Color::Blue;
    				line[1].position = sf::Vector2f(x, y) + normals[coordsToPix(x, y)] * LEN;
    				line[1].color = sf::Color::Blue;
    				target.draw(line, 2, sf::Lines);
    			}
    		}
    	}
    }
};

#endif
