#ifndef BOMBE_HPP
#define BOMBE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"
#include "weapon.hpp"

class Bombe : public Weapon {

public:

    Bombe(int &identification,int x, int y,sf::Vector2f traj);

    ~Bombe();

    //void teste();

    void fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects);

};



#endif