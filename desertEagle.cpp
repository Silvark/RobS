#include "desertEagle.hpp"
#include "Map.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40


Desert::Desert(){
}

Desert::Desert(int &idenification,int x, int y){

    hauteurobjet = 4;
    largeurobjet = 8;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    posX = x;
    posY = y;
    radius =10;

    sf::Vector2f traj;
    traj.x = 0;
    traj.y = 0;

    trajectoire = traj;
    body = Bd ;
    body.setPosition(x,y);
    id = idenification;
    idenification ++;
    sf::CircleShape expl(0);
    degats_explosion = expl;
    degats_explosion.setFillColor(sf::Color(255, 230,0));


}

void Desert::fctgravity(Map& level){

    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(this->trajectoire)){
        sf::Vector2f traj = this->trajectoire;

        if(level.getPixel(position.x+traj.x, position.y + this->hauteurobjet+traj.y) == false && level.getPixel(position.x + this->largeurobjet+traj.x, position.y + this->hauteurobjet+traj.y) == false){
            traj.y = traj.y + 0.1;
            this->trajectoire = traj;

        }
        else{
            traj.y = 0;
            while(level.getPixel(position.x+traj.x, position.y + this->hauteurobjet+traj.y) == false && level.getPixel(position.x + this->largeurobjet+traj.x, position.y + this->hauteurobjet+traj.y) == false){
                traj.y = traj.y + 0.1;
            }
            explode(level, position.x+traj.x+ this->largeurobjet/2, position.y + traj.y + this->hauteurobjet/2);
            std::cout << "BOOOM" << '\n';
        }

    }
}
