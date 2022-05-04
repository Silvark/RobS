#include "weapon.hpp"
#include "maping.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40

void Weapon::explode(std::vector<std::vector<int>> & level,int posX,int posY){

    for(int i = posX - this->radius; i <= posX + this->radius; i++)
    {
        for(int j = posY - radius; j <= posY + this->radius; j++)
        {
            if((i-posX)*(i-posX) + (j-posY)*(j-posY) < this->radius*this->radius)
            {

                if(i > 0 && i < fenetrecasehauteur && j < fenetrecaselargeur && j > 0){
                    if(level[i][j] == 1){
                        level[i][j]= 0;
                    }
                }
           }
       }
   }
}

bool Weapon::sortiemap(sf::Vector2f deplacement){

    if (this->posX + deplacement.x+this->largeurobjet >= taillebloc*fenetrecaselargeur || this->posX + deplacement.x < 0 || this->posY + deplacement.y +this->hauteurobjet >= taillebloc*fenetrecasehauteur ||this->posY + deplacement.y < 0){
        return 0;
    }
    else{
        return 1;
    }
}


void Weapon::fctgravity(std::vector<std::vector<int>> & level,Map & map,std::array<sf::RectangleShape, 4> & rects){

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
            explode(level,positiontableau(this->posY+this->hauteurobjet/2),positiontableau(this->posX+this->largeurobjet/2));
            std::cout << "BOOOM" << '\n';
            map.carte = map.tilesmaping(level, rects);
            traj.y = 2000;
            this->trajectoire = traj;
        }

    }
}
