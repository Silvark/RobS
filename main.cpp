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

    Map level("test2.png");
    sf::RenderWindow window(sf::VideoMode(level.getSize().x, level.getSize().y), "RobS");

    int id_courrant = 0;

    sf::Vector2f traj1;

    sf::Vector2f trajectory;
    bool target =0;
    sf::Vector2f targetPoint;

    int sizeEntity;

    traj1.x = 0;
    traj1.y = 0;

    Bombe b1(id_courrant,-10,0,traj1);
    Desert d1(id_courrant,-10,0,traj1);
    Mine m1(id_courrant,-10,0,traj1);

    Joueur j1(id_courrant,750,150);
    Joueur j2(id_courrant,300,150);

    std::vector<Entity *> entitee;
    entitee.push_back(&b1);
    entitee.push_back(&d1);
    entitee.push_back(&m1);
    entitee.push_back(&j1);
    entitee.push_back(&j2);

    int weapon_courrante;
    std::vector<Weapon *> weapon_list;
    weapon_list.push_back(&b1);
    weapon_list.push_back(&d1);
    weapon_list.push_back(&m1);

    int player = 0;
    std::vector<Joueur*> player_list;
    player_list.push_back(&j1);
    player_list.push_back(&j2);

    sf::Vector2f position_target;
    position_target.x = 0;
    position_target.y = 0;

    sf::RectangleShape body_target(sf::Vector2f(4, 4));
    body_target.setFillColor((sf::Color::Red));

    //std::cout << "taille liste" << '\n';
    //std::cout << player_list.size() << '\n';

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Right){

                    targetPoint.x = event.mouseButton.x;
                    targetPoint.y = event.mouseButton.y;
                    trajectory = vecteurDirecteur(targetPoint,player_list[player]->posX, player_list[player]->posY);
                    target = 1;
                    body_target.setPosition(targetPoint.x-2,targetPoint.y-2);

                }

                if (event.mouseButton.button == sf::Mouse::Left){

                    if(target == 1){
                        weapon_list[weapon_courrante]->trajectoire = trajectory;
                        weapon_list[weapon_courrante]->body.setPosition(player_list[player]->posX+player_list[player]->largeurobjet/2, player_list[player]->posY+player_list[player]->hauteurobjet/2);
                        target = 0;
                    }
                }

            }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && j1.inAir == 0)
                {
                    player_list[player]->saut();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& j1.inAir == 0)
                {
                    player_list[player]->deplacement(1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& j1.inAir == 0)
                {
                    player_list[player]->deplacement(2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                {
                    weapon_courrante = 0;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                {
                    weapon_courrante = 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
                {
                    weapon_courrante = 2;
                }




            if(event.type = sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::D)
                {
                    player_list[player]->deplacement(3);
                }
                if (event.key.code == sf::Keyboard::Q)
                {
                    player_list[player]->deplacement(3);
                }
                if (event.key.code == sf::Keyboard::P)
                {
                        player = player+1;
                        if(player>player_list.size()-1){
                            player = 0;
                    };
                    std::cout << player << '\n';
                }
            }
        }

        window.clear(sf::Color(128, 128, 128, 255));

        sizeEntity = entitee.size();

        for ( int i = 0; i< sizeEntity;i++){
            (entitee[i])->fctgravity(level);
            (entitee[i])->body.move((entitee[i])->trajectoire);
            window.draw((entitee[i])->body);
        }

        for ( int p = 0; p< player_list.size();p++){
            if(player != p){
                for ( int w = 0; w< weapon_list.size();w++){
                    (player_list[p])->collision(*weapon_list[w]);
                }
            }
            player_list[p]->mort(entitee,player_list);
        }

        window.draw(body_target);

        std::cout << "j1 : "<<j1.pv << '\n';
        std::cout << "j2 : "<<j2.pv << '\n';

        window.draw(level);
        window.display();
        usleep(50000);
    }

    return 0;
}
