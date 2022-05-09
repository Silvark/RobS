#ifndef DESERTEAGLE_HPP
#define DESERTEAGLE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.hpp"
#include "weapon.hpp"

class Desert : public Weapon {

public:

    Desert();

    Desert(int &identification,int x, int y,sf::Vector2f traj);
    void fctgravity(Map& map);

};



#endif
