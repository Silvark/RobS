#include "headers/Game.hpp"
#include "headers/Entity.hpp"

Entity::Entity() {
  position = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);
  texture = new sf::Texture();
  sprite = new sf::Sprite();
  alive = true;
  inMidair = true;
}

Entity::~Entity() {
  delete texture;
  delete sprite;
  delete hitbox;
}

void Entity::updateVelocity() {
  // update vitesse
  if (velocity.x < 1) {
    // ajout des frottements de l'air? :')
    velocity.x += 0;
  }
  if (velocity.y < 1 && inMidair) {
    velocity.y += GRAVITY/1e4 * 1/60;
  }
}
