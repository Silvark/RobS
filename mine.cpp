#include "mine.hpp"
#include "maping.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40

Mine::Mine(int &idenification,int x, int y,sf::Vector2f traj){

    hauteurobjet = 3;
    largeurobjet = 8;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    posX = x;
    posY = y;
    radius = 5;
    trajectoire = traj;
    body = Bd ;
    body.setPosition(x,y);
    id = idenification;
    idenification ++;
}

Mine::~Mine(){
}

void Mine::fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects){

    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(this->trajectoire)){

        sf::Vector2f traj = this->trajectoire;

        if(level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX+this->largeurobjet)]!=1){
            traj.y = traj.y + 5;
            this->trajectoire = traj;
        }
        else{
            traj.y = 0;
            while(level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX+this->largeurobjet)]!=1){
                traj.y = traj.y +0.1;
            }
            traj.x = 0;
            this->trajectoire = traj;
        }

    }
}
