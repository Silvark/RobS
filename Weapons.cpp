#include "headers/Game.hpp"
#include "headers/Player.hpp"
#include "headers/Weapons.hpp"

Weapon::Weapon() {
  alive = true;
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

void Weapon::onCollision(Game * game) {
  explode(game);
  alive = false;
}

void Weapon::move(Game * game) {
  Map * terrain = game->getMap();
  bool collides;

  sf::Vector2f initialPosition = this->getPosition();
  sf::Vector2f finalPosition;
  sf::Vector2f displacement;
  sf::FloatRect midpoint = sprite->getLocalBounds();

  initialPosition.x += midpoint.width/2;
  initialPosition.y += midpoint.height/2;

  finalPosition.x = initialPosition.x + velocity.x;
  finalPosition.y = initialPosition.y + velocity.y;

  displacement.x = finalPosition.x - initialPosition.x;
  displacement.y = finalPosition.y - initialPosition.y;

  sf::Vector2f intermediatePosition;
  float resolution = 0.05;

  for (float increment = 0; increment < 1; increment = increment + resolution) {
    intermediatePosition.x = initialPosition.x + displacement.x * increment;
    intermediatePosition.y = initialPosition.y + displacement.y * increment;

    try {
    collides = terrain->getPixel(floor(intermediatePosition.x), floor(intermediatePosition.y))
    && terrain->getPixel(ceil(intermediatePosition.x), ceil(intermediatePosition.y));
    }
    catch (const std::invalid_argument& except) {
      // oob
      collides = false;
      alive = false;
      return;
    }

    if (collides) {
      intermediatePosition.x -= midpoint.width/2;
      intermediatePosition.y -= midpoint.height/2;
      this->setPosition(intermediatePosition);
      onCollision(game);
      return;
    }
  }
  finalPosition.x -= midpoint.width/2;
  finalPosition.y -= midpoint.height/2;
  this->setPosition(finalPosition);
  return;
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sprite->setPosition(position.x, position.y);
  target.draw(*sprite, states);
}

void Weapon::explode(Game * game) {

}

Bomb::Bomb(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  mass = 20;
  velocity.x = velocity.x / mass;
  velocity.y = velocity.y / mass;

  blastRadius = 20;
  nBounces = 0;

  texture->loadFromFile("assets/bomb.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sprite->setScale(1/2, 1/2);

  hitbox = new sf::CircleShape(15);
  hitbox->setPosition(position);
}
Bomb::~Bomb() {}

Deagle::Deagle(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  mass = 5;
  velocity.x = velocity.x / mass;
  velocity.y = velocity.y / mass;

  blastRadius = 10;
  nBounces = 0;

  texture->loadFromFile("assets/deagle.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sprite->setScale(1/6, 1/6);

  hitbox = new sf::CircleShape(5);
  hitbox->setPosition(position);
}
Deagle::~Deagle() {}

Mine::Mine(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  mass = 40;
  velocity.x = velocity.x / mass;
  velocity.y = -velocity.y / mass; // le sol est vers les +, le ciel vers les -

  blastRadius = 50;
  nBounces = 0;

  texture->loadFromFile("assets/mine.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sprite->setScale(1/3, 1/3);

  hitbox = new sf::RectangleShape(sf::Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height));
  hitbox->setPosition(sf::Vector2f(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top));
}
Mine::~Mine() {}

WeaponItem::WeaponItem(int c, int p) {
  count = c;
  payload = p;
}

Weapon * WeaponItem::generateWeapon(Game * game, Player * player) {
  Rob * rob = player->getControlledRob();
  sf::Vector2f pos = rob->getPosition();
  pos.x = rob->getAimVector().x * 3;
  pos.y = rob->getAimVector().y * 3;
  sf::Vector2f vel(rob->getStrength(), rob->getStrength());
  Weapon * current = nullptr;

  if (payload == 0) {
    std::cout << "[WARN] Pas d'arme sélectionnée! "<< std::endl;
  }
  else {
    player->setHasPlayed(true);
    if (payload == 0) {
      current = new Bomb(pos, vel);
    }
    if (payload == 1) {
      current = new Deagle(pos, vel);
    }
    if (payload == 2) {
      current = new Mine(pos, vel);
    }
    if (payload > 2) {
      std::cout << "[WARN] Arme sélectionnée non reconnue! "<< std::endl;
      player->setHasPlayed(false);
    }
  }
  return current;
}
