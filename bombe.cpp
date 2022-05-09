#include "bombe.hpp"
#include "Map.hpp"
#include "fonctionUtiles.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40


Bombe::Bombe(int &idenification,int x, int y,sf::Vector2f traj){

    hauteurobjet = 10;
    largeurobjet = 10;
    sf::RectangleShape Bd(sf::Vector2f(largeurobjet, hauteurobjet));
    posX = x;
    posY = y;
    trajectoire = traj;
    radius = 10;
    body = Bd ;
    body.setPosition(x,y);
    id = idenification;
    idenification ++;
}

void Bombe::fctgravity(Map& level){

      sf::Vector2f position;
      position = this->body.getPosition();
      this->posX = position.x;
      this->posY = position.y;

      if(sortiemap(this->trajectoire)){

          sf::Vector2f traj = this->trajectoire;

          if(level.getPixel(posX, posY + hauteurobjet) == false && level.getPixel(posX + largeurobjet, posY + hauteurobjet) == false){
              traj.y = traj.y + 1;
              this->trajectoire = traj;
          }
          else{
              traj.y = 0;
              while(level.getPixel(posX, posY + hauteurobjet) == false && level.getPixel(posX + largeurobjet, posY + hauteurobjet) == false){
                  traj.y = traj.y + 0.1;
              }
              explode(level, posX + traj.x + largeurobjet/2, posY + traj.y + hauteurobjet/2);
              std::cout << "BOOOM" << '\n';
              traj.y = 2000;
              this->trajectoire = traj;
          }

      }
  }
