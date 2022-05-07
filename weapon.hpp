#ifndef WEAPON_HPP
#define WEAPON_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"
#include "entity.hpp"

class Weapon : public Entity{

public:

    void explode(std::vector<std::vector<int>> & level,int posX,int posY);
    //void teste();
    int radius;
};


#endif
