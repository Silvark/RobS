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

    sf::Vector2f trajectory;
    bool target =0;
    sf::Vector2f targetPoint;

    int size_entity_list;
    int size_player_list;
    int size_weapon_List;

    Bombe b1(id_courrant,-10,0);
    Desert d1(id_courrant,-10,0);
    Desert d2(id_courrant,-10,0);

    Mine m1(id_courrant,-10,0,1);
    Mine m2(id_courrant,-10,0,1);
    Mine m3(id_courrant,-10,0,1);
    Mine m4(id_courrant,-10,0,2);
    Mine m5(id_courrant,-10,0,2);
    Mine m6(id_courrant,-10,0,2);

    int mine_courrante = 3;

    Joueur j1(id_courrant,750,150,1);
    Joueur j2(id_courrant,300,150,2);


    std::vector<Entity *> entitee;
    entitee.push_back(&j1);
    entitee.push_back(&j2);
    entitee.push_back(&d2);

    int weapon_courrante = 0;
    std::vector<Weapon *> weapon_list;
    weapon_list.push_back(&b1);
    weapon_list.push_back(&d1);
    weapon_list.push_back(&d2);
    weapon_list.push_back(&m1);
    weapon_list.push_back(&m2);
    weapon_list.push_back(&m3);
    weapon_list.push_back(&m4);
    weapon_list.push_back(&m5);
    weapon_list.push_back(&m6);

    int player = 0;
    std::vector<Joueur*> player_list;
    player_list.push_back(&j1);
    player_list.push_back(&j2);


    sf::Vector2f position_target;
    position_target.x = 0;
    position_target.y = 0;

    sf::RectangleShape body_target(sf::Vector2f(4, 4));
    body_target.setFillColor((sf::Color::Red));

    sf::RectangleShape eau(sf::Vector2f(level.getSize().x, level.getSize().y));
    eau.setFillColor(sf::Color(0,0,255,128));
    int hauteurEau = level.getSize().y;
    eau.setPosition(0,hauteurEau);

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

                        entitee.pop_back();
                        std::cout << "cava" << '\n';
                        if (weapon_courrante==2){
                            if(mine_courrante==9){
                                entitee.erase(entitee.begin()+2);
                                mine_courrante = 3;
                            }
                            entitee.push_back(weapon_list[mine_courrante]);
                            entitee.push_back(weapon_list[mine_courrante]);
                            mine_courrante +=1;
                        }
                        else{
                            entitee.push_back(weapon_list[weapon_courrante]);
                        }

                        sf::Vector2f position;
                        if(targetPoint.x<player_list[player]->posX){
                            position.x = player_list[player]->posX-5;
                        }
                        else{
                            position.x = player_list[player]->posX+player_list[player]->largeurobjet+5;
                        }

                        position.y = player_list[player]->posY+player_list[player]->hauteurobjet/2;

                        entitee[entitee.size()-1]->trajectoire = trajectory;
                        entitee[entitee.size()-1]->body.setPosition(position.x,position.y);

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
                        hauteurEau -=10;
                        eau.setPosition(0,hauteurEau);

                    }
                }
            }
        }

        window.clear(sf::Color(128, 128, 128, 255));

        size_entity_list = entitee.size();
        size_player_list = player_list.size();
        size_weapon_List = weapon_list.size();

        for ( int i = 0; i< size_entity_list;i++){
            (entitee[i])->update(window,level);
        }


        for ( int p = 0; p< size_player_list;p++){
            if((player_list[p])->collisionEau(eau)){
                player_list[p]->mort(entitee,player_list,level);
            }
            else{
                for ( int w = 0; w< size_weapon_List;w++){
                    (player_list[p])->collisionWeapon(*weapon_list[w],level);
                }
                player_list[p]->mort(entitee,player_list,level);
            }
        }

        window.draw(level);
        window.draw(eau);
        window.draw(body_target);
        window.display();
        usleep(50000);
    }

    return 0;
}
