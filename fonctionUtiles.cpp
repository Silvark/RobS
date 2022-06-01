#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "weapon.hpp"

#define taillebloc 10

int positiontableau(float p){
    int x  = (int)std::floor(p/taillebloc);
    return x;
}

sf::Vector2f vecteurDirecteur(sf::Vector2f click,int pox, int poy){

    sf::Vector2f retour;
    retour.x = (click.x - pox)*0.05;
    retour.y = (click.y - poy)*0.05;
    std::cout << "x: " << retour.x << std::endl;
    std::cout << "y: " << retour.y << std::endl;
    return retour;

}

/*void rotationProjectile(Weapon& Projectile){

    int angle;
    angle = atan2(Projectile.trajectoire.x,Projectile.trajectoire.y);
    Projectile.body.setRotation(angle);

}*/

int DistancePoint(int p1x, int p1y,int p2x, int p2y){

    int retour;
    std::cout << p1x << " " <<p2x <<" " <<p1y<<" " <<p2y << '\n';
    retour = sqrt(pow((p2x-p1x),2)+pow((p2y-p1y),2));
    std::cout << retour << '\n';
    return retour;

}
