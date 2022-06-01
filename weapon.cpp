#include "weapon.hpp"
#include "Map.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

void Weapon::explode(Map& map,int posX,int posY){
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

   this->degats_explosion.setPosition(posX+this->largeurobjet/2-this->radius+this->trajectoire.x,posY+this->hauteurobjet/2-this->radius+this->trajectoire.y);
   this->degats_explosion.setRadius(this->radius);
   this->body.setPosition(2000,2000);
}
