#include "joueur.hpp"
#include "fonctionUtiles.hpp"
#include "Map.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40


Joueur::Joueur(int &idenification,int x, int y){

    hauteurobjet = 10;
    largeurobjet = 10;
    regard = 0;
    inAir = 1;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    Bd.setFillColor(sf::Color::Cyan);
    posX = x;
    posY = y;
    trajectoire.x = 0;
    trajectoire.y = 0;
    body = Bd ;
    body.setPosition(x,y);
    id = idenification;
    idenification ++;
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
            traj.y = traj.y + 1;
            this->trajectoire = traj;
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

        //else{


        //}
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


/*
void Joueur::collision(std::vector<std::vector<int>> & level){

    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(this->trajectoire)){

        sf::Vector2f traj = this->trajectoire;

        if(level[positiontableau(this->posY)][positiontableau(this->posX+this->largeurobjet+this->traj.y)]!=1 && level[positiontableau(this->posY)][positiontableau(this->posX+this->trajectoire)]!=1){
            traj.x = traj.x + 1;
            this->trajectoire = traj;
        }
        else{
            traj.y = 0;
            while(level[positiontableau(this->posY)][positiontableau(this->posX+this->largeurobjet+this->traj.y)]!=1 && level[positiontableau(this->posY)][positiontableau(this->posX+this->trajectoire)]!=1){
                traj.x = traj.x + 0.1;
            }
            this->trajectoire = traj;

        }
    }
}*/
