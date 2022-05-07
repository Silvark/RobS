#ifndef ENTITY_HPP
#define ENTITY_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "maping.hpp"

class Entity{

public:

    bool sortiemap(sf::Vector2f deplacement);
    void fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects);

    //void teste();

    //void deplaceentity(std::list<Entity> entity,std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects);


    sf::RectangleShape body;
    int posX;
    int posY;
    sf::Vector2f trajectoire;
    int hauteurobjet;
    int largeurobjet;
    int id;


};



#endif
