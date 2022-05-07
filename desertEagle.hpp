#ifndef DESERTEAGLE_HPP
#define DESERTEAGLE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"
#include "weapon.hpp"

class Desert : public Weapon {

public:

    Desert();
    //void teste();
    Desert(int &identification,int x, int y,sf::Vector2f traj);
    void fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects);

};



#endif
