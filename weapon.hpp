#ifndef WEAPON_HPP
#define WEAPON_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"
#include "entity.hpp"

class Weapon : public Entity{

public:
    virtual void fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects) =0;
    void explode(std::vector<std::vector<int>> & level,int posX,int posY);

    int radius;
};


#endif
