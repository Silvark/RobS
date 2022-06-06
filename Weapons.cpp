#include "headers/Weapons.hpp"

Weapon::Weapon() {
  position = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0, 0);

  texture->loadFromFile("assets/placeholder.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
}

Weapon::Weapon(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  texture->loadFromFile("assets/placeholder.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
}

void Weapon::move(Game * game) {
  Map * terrain = game->getMap();
  if (position.x > terrain->getSize().x + 50 || position.y > terrain->getSize().y + 50
   || position.x < -50 || position.y < -50) {
    // out of bounds
    alive = false;
  }

  float gravity = (mass * -9.81);
  sf::Vector2f finalPosition(position.x + (velocity.x * (1/60)), position.y + (velocity.y * (1/60)) + gravity);

  sf::Vector2f displacement(finalPosition.x - position.x, finalPosition.y - position.y);
  for (int increment = 0; increment < 100; increment + RESOLUTION) {
    
  }


}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*sprite, states);
}

void Weapon::explode(Game * game) {

}

Bomb::Bomb(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  blastRadius = 50;
  mass = 0.1;
  nBounces = 0;

  texture->loadFromFile("assets/bomb.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sprite->setScale(1/2, 1/2);

  hitbox = new sf::CircleShape(30);
  hitbox->setPosition(position);
}
Bomb::~Bomb() {}

Deagle::Deagle(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  blastRadius = 10;
  mass = 1;
  nBounces = 0;

  texture->loadFromFile("assets/deagle.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sprite->setScale(1/6, 1/6);

  hitbox = new sf::CircleShape(10);
  hitbox->setPosition(position);
}
Deagle::~Deagle() {}

Mine::Mine(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  blastRadius = 20;
  mass = 1;
  nBounces = 0;

  texture->loadFromFile("assets/mine.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sprite->setScale(1/3, 1/3);

  hitbox = new sf::RectangleShape(sprite->getGlobalBounds());
}
Mine::~Mine() {}

WeaponItem::WeaponItem(int c, int p) {
  count = c;
  payload = p;
}

void WeaponItem::generateWeapon(Game * game) {
  switch (payload) {
    case 0: // bombe
      break;
    case 1: // deagle
      break;
    case 2: // mine
      break;
  }
}
