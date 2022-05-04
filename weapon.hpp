#ifndef WEAPON_HPP
#define WEAPON_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"

class Weapon{

public:

    void explode(std::vector<std::vector<int>> & level,int posX,int posY);
    bool sortiemap(sf::Vector2f deplacement);
    void fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects);

    sf::RectangleShape body;
    int posX;
    int posY;
    int radius;
    sf::Vector2f trajectoire;
    int hauteurobjet;
    int largeurobjet;

};


#endif
