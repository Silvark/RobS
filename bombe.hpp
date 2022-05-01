#ifndef BOMBE_HPP
#define BOMBE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include "maping.hpp"

class Bombe{

public:

    Bombe(int x, int y);
    void explode(std::vector<std::vector<int>> & level,int posX,int posY);
    bool sortiemap(sf::Vector2f deplacement);
    void fctgravity(std::vector<std::vector<int>> & level,sf::Vector2f & gravity,Map & map,std::array<sf::RectangleShape, 4> & rects);

    sf::RectangleShape body;
    int posX;
    int posY;
    int radius;
    sf::Vector2f gravity;

};

int positiontableau(float p);


#endif
