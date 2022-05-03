#ifndef DESERTEAGLE_HPP
#define DESERTEAGLE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"
#include "weapon.hpp"

class Desert : public Weapon {

public:

    Desert(int x, int y);
    void fctgravity(std::vector<std::vector<int>> & level,sf::Vector2f & gravity,Map & map,std::array<sf::RectangleShape, 4> & rects);

    //sf::RectangleShape body;
    //int posX;
    //int posY;
    //int radius;
    //sf::Vector2f gravity;

};



#endif
