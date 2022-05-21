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
#include "joueur.hpp"


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

    int sizeEntity;


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

    Joueur j1(id_courrant,750,150);


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Right){

                    std::cout << "visee" << "\n";
                    targetPoint.x = event.mouseButton.x;
                    targetPoint.y = event.mouseButton.y;
                    trajectory = vecteurDirecteur(targetPoint,10, 150);
                    target = 1;
                }

                if (event.mouseButton.button == sf::Mouse::Left){


                    if(target == 1){
                        //b2.trajectoire = trajectory;
                        //weap.push_back(&b2);
                        std::cout << "tireeee" << '\n';
                        target = 0;
                    }
                }

            }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && j1.inAir == 0)
                {
                    j1.saut();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& j1.inAir == 0)
                {
                    j1.deplacement(1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& j1.inAir == 0)
                {
                    j1.deplacement(2);
                }


            if(event.type = sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::D)
                {
                    j1.deplacement(3);
                }
                if (event.key.code == sf::Keyboard::Q)
                {
                    j1.deplacement(3);
                }
            }

        }

        window.clear(sf::Color(128, 128, 128, 255));

        sizeEntity = weap.size();

        for ( int i = 0; i< sizeEntity;i++){
            (weap[i])->fctgravity(level);
            (weap[i])->body.move((weap[i])->trajectoire);
            window.draw((weap[i])->body);
        }

        j1.fctgravity(level);
        j1.body.move(j1.trajectoire);
        window.draw(j1.body);

        window.draw(level);
        window.display();
        usleep(50000);
    }

    return 0;
}
