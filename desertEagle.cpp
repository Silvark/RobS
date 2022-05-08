#include "desertEagle.hpp"
#include "maping.hpp"
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

Desert::Desert(int &idenification,int x, int y,sf::Vector2f traj){

    hauteurobjet = 4;
    largeurobjet = 8;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    posX = x;
    posY = y;
    radius = 3;
    trajectoire = traj;
    body = Bd ;
    body.setPosition(x,y);
    id = idenification;
    idenification ++;
}

void Desert::fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects){

    std::cout << "/* mes */" << '\n';
    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(this->trajectoire)){

        sf::Vector2f traj = this->trajectoire;

        if(level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX+this->largeurobjet)]!=1){
            traj.y = traj.y + 0.1;
            this->trajectoire = traj;
        }
        else{
            traj.y = 0;
            while(level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX+this->largeurobjet)]!=1){
                traj.y = traj.y + 0.1;
            }
            explode(level,positiontableau(this->posY+this->hauteurobjet/2),positiontableau(this->posX+this->largeurobjet/2));
            std::cout << "BOOOM" << '\n';
            map.carte = map.tilesmaping(level, rects);
            traj.y = 2000;
            this->trajectoire = traj;
        }

    }
}

/*void Desert::teste(){
    std::cout << "desert" << '\n';
}*/