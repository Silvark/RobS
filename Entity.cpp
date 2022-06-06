#include "headers/Entity.hpp"

Entity::Entity() {
  position = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);
  alive = true;
}

Entity::~Entity() {
  delete texture;
  delete sprite;
  delete hitbox;
}
