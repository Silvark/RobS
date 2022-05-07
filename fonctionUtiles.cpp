#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define taillebloc 10

int positiontableau(float p){
    int x  = (int)std::floor(p/taillebloc);
    return x;
}

sf::Vector2f vecteurDirecteur(sf::Vector2f click,int pox, int poy){

    sf::Vector2f retour;
    retour.x = click.x - pox;
    retour.y = click.y - poy;
    std::cout << "x: " << retour.x << std::endl;
    std::cout << "y: " << retour.y << std::endl;
    return retour;

}
