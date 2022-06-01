#include "entity.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>

#define XLIM 1920
#define YLIM 1080


bool Entity::sortiemap(sf::Vector2f deplacement){

    if (this->posX + deplacement.x+this->largeurobjet >= XLIM || this->posX + deplacement.x < 0 || this->posY + deplacement.y +this->hauteurobjet >= YLIM ||this->posY + deplacement.y < 0){
        return 0;
    }
    else{
        return 1;
    }
}

Entity::Entity(){
    hauteurobjet = 5;
    largeurobjet = 5;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    Bd.setFillColor(sf::Color::Red);
    body = Bd ;
}

void Entity::explode(Map& map,int posX,int posY){
    int minX = posX, minY = posY;
    for(int i = posX - this->radius; i <= posX + this->radius; i++)
    {
        for(int j = posY - radius; j <= posY + this->radius; j++)
        {
            if((i-posX)*(i-posX) + (j-posY)*(j-posY) < this->radius*this->radius)
            {

                if(i > 0 && i < map.getSize().x && j < map.getSize().y && j > 0){
                    if(map.getPixel(i, j) == 1){
                        map.setPixel(i, j, 0);
                    }
                    if (i < minX) {minX = i;}
                    if (j < minY) {minY = j;}
                }
           }
       }
   }
   map.updateMap(minX, minY, (this->radius*2), (this->radius)*2);

   this->degats_explosion.setPosition(posX+this->largeurobjet/2-this->radius,posY+this->hauteurobjet/2-this->radius);
   this->degats_explosion.setRadius(this->radius);
}

void Entity::update(sf::RenderWindow& window, Map& level){

    this->fctgravity(level);
    this->body.move(this->trajectoire);

    window.draw(this->degats_explosion);
    window.draw(this->body);

    this->degats_explosion.setRadius(0);
    sf::Vector2f position = this->body.getPosition();
    this->degats_explosion.setPosition(position.x,position.y);
}
