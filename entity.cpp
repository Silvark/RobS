#include "entity.hpp"
#include "maping.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40


bool Entity::sortiemap(sf::Vector2f deplacement){

    if (this->posX + deplacement.x+this->largeurobjet >= taillebloc*fenetrecaselargeur || this->posX + deplacement.x < 0 || this->posY + deplacement.y +this->hauteurobjet >= taillebloc*fenetrecasehauteur ||this->posY + deplacement.y < 0){
        return 0;
    }
    else{
        return 1;
    }
}


void Entity::fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects){

    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(this->trajectoire)){

        sf::Vector2f traj = this->trajectoire;

        if(level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX+this->largeurobjet)]!=1){
            traj.y = traj.y + 0.1;
        }
        else{
            traj.y = 0;
            while(level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+traj.y+this->hauteurobjet)][positiontableau(this->posX+this->largeurobjet)]!=1){
                traj.y = traj.y + 0.1;
            }
            traj.x = 0;
            this->trajectoire = traj;
        }

    }
}
