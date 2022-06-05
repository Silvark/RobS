#include "Entity.hpp"
#include <iostream>

Entity::Entity() {
  position = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);
}

Entity::~Entity() {
  delete sprite;
}
