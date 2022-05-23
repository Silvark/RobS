#ifndef FONCTIONUTILES_HPP
#define FONCTIONUTILES_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
#include "weapon.hpp"

int positiontableau(float p);

sf::Vector2f vecteurDirecteur(sf::Vector2f click,int pox, int poy);

void rotationProjectile(Weapon& Projectile);

#endif
