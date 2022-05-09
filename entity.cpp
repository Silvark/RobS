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
