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
#define hauteurjoueur 10
#define largeurjoueur 10

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

    if (this->posX + deplacement.x+largeurjoueur >= taillebloc*fenetrecaselargeur || this->posX + deplacement.x < 0 || this->posY + deplacement.y +hauteurjoueur >= taillebloc*fenetrecasehauteur ||this->posY + deplacement.y < 0){
        return 0;
    }
    else{
        return 1;
    }
}

void Weapon::fctgravity(std::vector<std::vector<int>> & level,sf::Vector2f & gravity,Map & map,std::array<sf::RectangleShape, 4> & rects){

    sf::Vector2f position;
    position = this->body.getPosition();
    this->posX = position.x;
    this->posY = position.y;

    if(sortiemap(gravity)){

        if(level[positiontableau(this->posY+gravity.y+hauteurjoueur)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+gravity.y+hauteurjoueur)][positiontableau(this->posX+largeurjoueur)]!=1){
            gravity.y = gravity.y + 0.1;
        }
        else{
            gravity.y = 0;
            while(level[positiontableau(this->posY+gravity.y+hauteurjoueur)][positiontableau(this->posX)]!=1 && level[positiontableau(this->posY+gravity.y+hauteurjoueur)][positiontableau(this->posX+largeurjoueur)]!=1){
                gravity.y = gravity.y + 1;
            }
            explode(level,positiontableau(this->posY+hauteurjoueur/2),positiontableau(this->posX+largeurjoueur/2));
            std::cout << "BOOOM" << '\n';
            map.carte = map.tilesmaping(level, rects);
            gravity.y = 2000;
        }

    }
}
