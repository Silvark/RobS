#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<unistd.h>
#include <cmath>
#include <list>

#include "fonctionUtiles.hpp"

#include "Map.hpp"

#include "weapon.hpp"
#include "bombe.hpp"
#include "desertEagle.hpp"
#include "mine.hpp"

//g++ testBen.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40
#define hauteurjoueur 10
#define largeurjoueur 10


int main()
{

    Map level("test.png");
    sf::RenderWindow window(sf::VideoMode(level.getSize().x, level.getSize().y), "RobS");

    int id_courrant = 0;

    sf::Vector2f traj1;
    sf::Vector2f traj2;

    sf::Vector2f trajectory;
    bool target =0;
    sf::Vector2f targetPoint;


    traj1.x = 0;
    traj1.y = 0;

    traj2.x = 25;
    traj2.y = -1;

    Bombe b1(id_courrant,200,10,traj1);
    Desert d1(id_courrant,0,85,traj2);
    Mine m1(id_courrant,35,85,traj2);

    std::vector<Weapon *> weap;

    weap.push_back(&b1);
    weap.push_back(&d1);
    weap.push_back(&m1);


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){


                    if(target == 1){
                        //std::cout << "tire" << '\n';
                        target = 0;
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right){

                    //std::cout << "pos" << event.mouseButton.x << std::endl;
                    targetPoint.x = event.mouseButton.x;
                    targetPoint.y = event.mouseButton.y;
                    target = 1;
                }
            }
        }

        window.clear(sf::Color(128, 128, 128, 255));

        for ( int i = 0; i< weap.size();i++){
            (weap[i])->fctgravity(level);
            (weap[i])->body.move((weap[i])->trajectoire);
            window.draw((weap[i])->body);
        }

        window.draw(level);
        window.display();
        usleep(24000);
    }

    return 0;
}
