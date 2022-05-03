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
#define hauteurjoueur 10
#define largeurjoueur 10

Desert::Desert(int x, int y){

    sf::RectangleShape Bd(sf::Vector2f(2, 4));
    posX = x;
    posY = y;
    radius = 3;
    body = Bd ;
    body.setPosition(x,y);
}

void Desert::fctgravity(std::vector<std::vector<int>> & level,sf::Vector2f & gravity,Map & map,std::array<sf::RectangleShape, 4> & rects){

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
                gravity.y = gravity.y + 0.1;
            }
            explode(level,positiontableau(this->posY+hauteurjoueur/2),positiontableau(this->posX+largeurjoueur/2));
            std::cout << "BOOOM" << '\n';
            map.carte = map.tilesmaping(level, rects);
            gravity.y = 2000;
        }

    }
}
