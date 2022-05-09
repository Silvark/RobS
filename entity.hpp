#ifndef ENTITY_HPP
#define ENTITY_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Map.hpp"

class Entity{

public:

    bool sortiemap(sf::Vector2f deplacement);
    virtual void fctgravity(Map& map)= 0;



    sf::RectangleShape body;
    int posX;
    int posY;
    sf::Vector2f trajectoire;
    int hauteurobjet;
    int largeurobjet;
    int id;


};



#endif
