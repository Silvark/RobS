#include "Entity.hpp"

Entity::Entity() {
  position = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);
  health = 1;
  energy = 1;
  sf::Texture phtex;
  phtex.loadFromFile("assets/placeholder.png");
  sprite->setTexture(phtex);
}

Entity::Entity(sf::Vector2f pos, sf::Vector2f vel, int h, int e, sf::Texture * tex) {
  position = pos;
  velocity = vel;
  health = h;
  energy = e;
  sprite->setTexture(*tex);
}
