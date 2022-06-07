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
  std::cout << "dtor entity" << '\n';
  delete sprite;
  delete texture;
}

// gravité, effets physiques
void Entity::updateVelocity() {
  velocity.y += GRAVITY/1e4 * 1/60;
}

// déplacement
void Entity::updateVelocity(sf::Vector2f vel) {
  velocity += vel;
}
