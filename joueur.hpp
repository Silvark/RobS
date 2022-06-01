#ifndef JOUEUR_HPP
#define JOUEUR_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Map.hpp"
#include "entity.hpp"
#include "weapon.hpp"
#include "mine.hpp"

class Joueur : public Entity {

public:

    Joueur(int &idenification,int x, int y,int equipe);
    void fctgravity(Map& map);
    void saut();
    void deplacement(int dir);
    void collisionWeapon(Weapon& weap,Map& level);
    bool collisionEau(sf::RectangleShape& eau);
    void mort(std::vector<Entity *>& entitee,std::vector<Joueur*>& player_list,Map& level);

    bool regard;
    bool inAir;
    int pv;
    int team;

};



#endif
