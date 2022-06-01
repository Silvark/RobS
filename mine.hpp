#ifndef MINE_HPP
#define MINE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.hpp"
#include "weapon.hpp"

class Mine : public Weapon {

public:

    Mine(int &identification,int x, int y,int equipe);
    ~Mine();
    void fctgravity(Map& map);

    int team;
};



#endif
