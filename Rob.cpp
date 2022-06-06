#include "headers/Rob.hpp"

Rob::Rob(sf::Vector2f pos, sf::Vector2f vel, int type) {
  position = pos;
  velocity = vel;

  health = 100;
  energy = 100;

  isControlled = false;
  strength = 0;
  aimVector = sf::Vector2f(0, 0);

  texture = new sf::Texture();
  sprite = new sf::Sprite();

  selectorTexture = new sf::Texture();
  selectorSprite = new sf::Sprite();
  selectorTexture->loadFromFile("assets/pointer.png");
  selectorSprite->setTexture(*selectorTexture);
  selectorSprite->setPosition(sf::Vector2f(position.x, position.y + 15));

  switch (type) {
    case 1:
      texture->loadFromFile("assets/rob1.png");
      break;
    case 2:
      texture->loadFromFile("assets/rob2.png");
      break;
    default:
      texture->loadFromFile("assets/placeholder.png");
      break;
  }
  sprite->setTexture(*texture);
  sprite->setPosition(position);
}

Rob::~Rob() {
  delete sprite;
  delete texture;
  delete selectorSprite;
  delete selectorTexture;
}

sf::Vector2f Rob::calculateAimVector(sf::Vector2i& mousePos) {

}

float Rob::calculateStrength(sf::Vector2i& mousePos) {

}

void Rob::move(Game * game) {

}

void Rob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*sprite, states);
  if (isControlled) {
    target.draw(*selectorSprite, states);
  }
}