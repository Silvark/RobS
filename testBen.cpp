#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<unistd.h>
#include <cmath>

#define taillebloc 50
#define fenetrecaselargeur 31
#define fenetrecasehauteur 8
#define hauteurjoueur 20
#define largeurjoueur 20

std::vector<sf::RectangleShape> tilesmaping(const std::vector<std::vector<int>> & level , std::array<sf::RectangleShape, 4> rects){

    std::vector<sf::RectangleShape> map;

    for (int i = 0;i<fenetrecasehauteur;i++){
        for (int j = 0;j<fenetrecaselargeur;j++){

            rects[level[i][j]].setPosition(sf::Vector2f(j*taillebloc, i*taillebloc));

            map.push_back(rects[level[i][j]]);
            //std::cout << std::endl << level[i][j] << std::endl;
        }

    }

    return map;
}

void drawMap(const std::vector<sf::RectangleShape>& map, sf::RenderWindow& window){

    for(auto i : map)
        window.draw(i);
}

int positiontableau(float p){
    int x  = (int)std::floor(p/taillebloc);
    return x;
}

int main()
{
    //std::cout << "e";
    std::vector<std::vector<int>> level =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    sf::RenderWindow window(sf::VideoMode(fenetrecaselargeur*taillebloc, taillebloc*fenetrecasehauteur), "First try");

    sf::RectangleShape shape(sf::Vector2f(20,20));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(60, 60);

    sf::RectangleShape rouge(sf::Vector2f(taillebloc, taillebloc));
    rouge.setFillColor(sf::Color::Red);
    sf::RectangleShape vert(sf::Vector2f(taillebloc,taillebloc));
    vert.setFillColor(sf::Color::Green);
    sf::RectangleShape bleu(sf::Vector2f(taillebloc,taillebloc));
    bleu.setFillColor(sf::Color::Blue);
    sf::RectangleShape jaune(sf::Vector2f(taillebloc, taillebloc));
    jaune.setFillColor(sf::Color::Yellow);

    std::array<sf::RectangleShape, 4> rects {rouge, vert, bleu, jaune};

    int posX = 60,posY = 60,avancegravite = 0;
    int infG,infD,gravity=2,testdistance =1;

    int NposX,NposY;

    infG = posY+hauteurjoueur;
    infD = posY+hauteurjoueur+largeurjoueur;


    std::vector<sf::RectangleShape> map = tilesmaping(level, rects);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        if(level[positiontableau(posY+gravity+20)][positiontableau(posX)]!=1){
            gravity = gravity + 1;
        }
        else{
            gravity = 0;
            while(level[positiontableau(posY+gravity+20)][positiontableau(posX)]!=1){
                gravity = gravity + 1;
            }
        }

        shape.move(0,gravity);
        posY = posY + gravity;

        window.clear();
        drawMap(map, window);
        window.draw(shape);
        window.display();
        usleep(50000);
    }

    return 0;
}
