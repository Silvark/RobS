#include "joueur.hpp"
#include "fonctionUtiles.hpp"
#include "Map.hpp"
#include "weapon.hpp"
#include "mine.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40


Joueur::Joueur(int &idenification,int x, int y,int equipe){

    hauteurobjet = 10;
    largeurobjet = 10;
    regard = 0;
    inAir = 1;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    Bd.setFillColor(sf::Color::Green);
    posX = x;
    posY = y;
    trajectoire.x = 0;
    trajectoire.y = 0;
    body = Bd ;
    body.setPosition(x,y);
    pv = 50;
    id = idenification;
    idenification ++;
    team = equipe;
    body.setOutlineThickness(2);

    radius = 15;

    if(team == 1){
        body.setOutlineColor(sf::Color(0, 0, 255));
    }
    else{
        body.setOutlineColor(sf::Color(255, 0, 0));
    }

    sf::CircleShape expl(0);
    degats_explosion = expl;
    degats_explosion.setFillColor(sf::Color(255, 230,0));

}

void Joueur::fctgravity(Map& level){

    bool move = false;
    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(this->trajectoire)){

        sf::Vector2f traj = this->trajectoire;

        if(level.getPixel(position.x+traj.x, position.y + this->hauteurobjet+traj.y) == false && level.getPixel(position.x + this->largeurobjet+traj.x, position.y + this->hauteurobjet+traj.y) == false){
            //std::cout << "chute" << '\n';
            if(level.getPixel(position.x+traj.x, position.y + this->hauteurobjet+1) == false && level.getPixel(position.x + this->largeurobjet+traj.x, position.y + this->hauteurobjet+traj.y+1) == false){
                traj.y = traj.y + 1;
            }
            this->trajectoire = traj;
            /*if(traj.y>20){
                this->pv = 0;
            }*/
        }
        else {
            //std::cout << "chutelente" << '\n';
            traj.y = 0;
            while(level.getPixel(position.x+traj.x, position.y + this->hauteurobjet+traj.y) == false && level.getPixel(position.x + this->largeurobjet+traj.x, position.y + this->hauteurobjet+traj.y) == false){
                traj.y = traj.y + 0.1;
            }

            traj.x = 0;
            if(this->inAir == 1){
                traj.y = 0;
                traj.x = 0;
                this->inAir = 0;
            }
            else{
                traj.y = 0;
            }
            this->trajectoire = traj;
        }

    }
}

void Joueur::saut(){

    if(regard){
        this->trajectoire.x = -3;
        this->trajectoire.y = -10;
    }
    else{
        this->trajectoire.x = 3;
        this->trajectoire.y = -10;
    }
    this->inAir = 1;

};

void Joueur::deplacement(int dir){

    if(dir == 1){
        this->trajectoire.x = 10;
        this->regard = 0;
    }
    else if(dir == 2){
        this->trajectoire.x = -10;
        this->regard = 1;
    }
    else{
        this->trajectoire.x = 0;
    }
};



void Joueur::collisionWeapon(Weapon& weap,Map& level){

    sf::FloatRect joueurBoundingBox = this->body.getGlobalBounds();
    sf::FloatRect weapBoundingBox = weap.body.getGlobalBounds();
    sf::FloatRect weapRadiusBoundingBox = weap.degats_explosion.getGlobalBounds();

    if(joueurBoundingBox.intersects(weapBoundingBox)){
        std::cout << "colisisisi" << '\n';
        weap.explode(level, weap.posX + weap.largeurobjet/2, weap.posY+ weap.hauteurobjet/2);
        this->pv -= weap.radius;
        this->trajectoire.x = weap.trajectoire.x*0.5;
        this->trajectoire.y = weap.trajectoire.y*0.5;
        this->body.setFillColor(sf::Color(255+(255/100)*(100-this->pv), 255-(255/100)*(100-this->pv), 0));
    }
    else if(joueurBoundingBox.intersects(weapRadiusBoundingBox)){

        int distance = DistancePoint(this->posX,this->posY,weap.posX+weap.largeurobjet/2-weap.radius,weap.posY+weap.hauteurobjet/2-weap.radius);
        int perte = 0.5*distance+(weap.radius/2);
        this->pv -= perte;
        this->trajectoire.x = weap.trajectoire.x*0.5;
        this->trajectoire.y = weap.trajectoire.y*0.5;
        this->body.setFillColor(sf::Color(255+(255/100)*(100-this->pv), 255-(255/100)*(100-this->pv), 0));
    }

}

bool Joueur::collisionEau(sf::RectangleShape& eau){
    sf::FloatRect joueurBoundingBox = this->body.getGlobalBounds();
    sf::FloatRect eauBoundingBox = eau.getGlobalBounds();
    bool retour = 0;
    if(joueurBoundingBox.intersects(eauBoundingBox)){
        this->pv = 0;
        retour = 1;
    }
    return retour;
}


void Joueur::mort(std::vector<Entity *>& entitee,std::vector<Joueur*>& player_list,Map& level){

    if(this->pv <= 0){
        std::cout << "DCD" << '\n';
        this->explode(level,this->posX+this->largeurobjet/2,this->posY+this->hauteurobjet/2);
        for ( int i = 0; i< entitee.size();i++){
            if(entitee[i]->id==this->id){
                entitee.erase(entitee.begin()+i);
            }
        }
        for ( int i = 0; i< player_list.size();i++){
            if(player_list[i]->id==this->id){
                player_list.erase(player_list.begin()+i);
            }
        }
    }
}
