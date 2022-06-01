#include "mine.hpp"
#include "Map.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40

Mine::Mine(int &idenification,int x, int y,int equipe){

    hauteurobjet = 5;
    largeurobjet = 5;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    posX = x;
    posY = y;

    sf::Vector2f traj;
    traj.x = 0;
    traj.y = 0;


    radius = 20;
    trajectoire = traj;
    body = Bd ;
    body.setPosition(x,y);
    id = idenification;
    idenification ++;

    body.setOutlineColor(sf::Color(0, 0, 255));

    team = equipe;
    std::cout << "msss" << '\n';

    if(team == 1){
        body.setOutlineColor(sf::Color(0, 0, 255));
    }
    else{
        body.setOutlineColor(sf::Color(255, 0, 0));
    }
}

Mine::~Mine(){
}

void Mine::fctgravity(Map& level){

    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(this->trajectoire)){
        sf::Vector2f traj = this->trajectoire;

        if(level.getPixel(position.x+traj.x, position.y + this->hauteurobjet+traj.y) == false && level.getPixel(position.x + this->largeurobjet+traj.x, position.y + this->hauteurobjet+traj.y) == false){
            traj.y = traj.y + 1;
            this->trajectoire = traj;
        }
        else{
            traj.y = 0;
            while(level.getPixel(position.x+traj.x, position.y + this->hauteurobjet+traj.y) == false && level.getPixel(position.x + this->largeurobjet+traj.x, position.y + this->hauteurobjet+traj.y) == false){
                traj.y = traj.y + 0.1;
            }
            traj.x = 0;
            this->trajectoire = traj;
            //explode(level, position.x + traj.x + this->largeurobjet/2, position.y + traj.y + this->hauteurobjet/2);
            //std::cout << "BOOOM" << '\n';
            //traj.y = 2000;
            //this->trajectoire = traj;
        }

    }
  }

  //
