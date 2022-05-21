#ifndef JOUEUR_HPP
#define JOUEUR_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Map.hpp"
#include "entity.hpp"

class Joueur : public Entity {

public:

    Joueur(int &idenification,int x, int y);
    void fctgravity(Map& map);
    void saut();
    void deplacement(int dir);

    bool regard;
    bool inAir;

};



#endif
