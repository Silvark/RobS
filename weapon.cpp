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
