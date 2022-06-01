#ifndef WEAPON_HPP
#define WEAPON_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.hpp"
#include "entity.hpp"

class Weapon : public Entity{
protected:
public:
    virtual void fctgravity(Map& map) =0;
    void explode(Map& map,int posX,int posY);
};


#endif
