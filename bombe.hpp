#ifndef BOMBE_HPP
#define BOMBE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"
#include "weapon.hpp"

class Bombe : public Weapon {

public:

    Bombe(int x, int y);
    void fctgravity(std::vector<std::vector<int>> & level,sf::Vector2f & gravity,Map & map,std::array<sf::RectangleShape, 4> & rects);


};



#endif
