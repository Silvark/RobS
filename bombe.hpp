#ifndef BOMBE_HPP
#define BOMBE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.hpp"
#include "weapon.hpp"

class Bombe : public Weapon {

public:

    Bombe(int &identification,int x, int y);
    Bombe();

    void fctgravity(Map& map);

};



#endif
