#ifndef JOUEUR_HPP
#define JOUEUR_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Map.hpp"
#include "entity.hpp"
#include "weapon.hpp"

class Joueur : public Entity {

public:

    Joueur(int &idenification,int x, int y);
    void fctgravity(Map& map);
    void saut();
    void deplacement(int dir);
    void collision(Weapon& weap);
    void mort(std::vector<Entity *>& entitee,std::vector<Joueur*>& player_list);

    bool regard;
    bool inAir;
    int pv;

};



#endif
