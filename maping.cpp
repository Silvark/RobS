#include "maping.hpp"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#define taillebloc 10
#define fenetrecaselargeur 91
#define fenetrecasehauteur 40
#define hauteurjoueur 10
#define largeurjoueur 10

Map::Map(){
}


std::vector<sf::RectangleShape> Map::tilesmaping(const std::vector<std::vector<int>> & level , std::array<sf::RectangleShape, 4> rects){

    std::vector<sf::RectangleShape> map;

    for (int i = 0;i<fenetrecasehauteur;i++){
        for (int j = 0;j<fenetrecaselargeur;j++){

            rects[level[i][j]].setPosition(sf::Vector2f(j*taillebloc, i*taillebloc));

            map.push_back(rects[level[i][j]]);
        }

    }

    return map;
}

void Map::drawMap(sf::RenderWindow& window){

    for(auto i : this->carte)
        window.draw(i);
}
