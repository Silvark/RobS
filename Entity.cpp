#include "headers/Game.hpp"
#include "headers/Entity.hpp"

Entity::Entity() {
  position = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);
  texture = new sf::Texture();
  sprite = new sf::Sprite();
  alive = true;
  isControlled = false;
}

Entity::~Entity() {
  delete texture;
  delete sprite;
  delete hitbox;
}

// gravité, effets physiques
void Entity::updateVelocity() {
  velocity.y += GRAVITY/1e4 * 1/60;
  // if (velocity.x > 0.05) { velocity.x = 0.05; }
  // if (velocity.y > 0.5) { velocity.y = 0.5; }
}

// déplacement
void Entity::updateVelocity(sf::Vector2f vel) {
  velocity += vel;
}
