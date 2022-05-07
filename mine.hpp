#ifndef MINE_HPP
#define MINE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"
#include "weapon.hpp"

class Mine : public Weapon {

public:

    Mine(int &identification,int x, int y,sf::Vector2f traj);
    ~Mine();
    //void teste();
    void fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects);

};



#endif
