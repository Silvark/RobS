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
  std::cout << "[INFO] Explosion!" << std::endl;
  sf::FloatRect midpoint = sprite->getLocalBounds();
  sf::Vector2i midPos;
  midPos.x = position.x + midpoint.width/2;
  midPos.y = position.y + midpoint.height/2;

  for (int x = position.x; x < position.x + 2*blastRadius; x++) {
    for (int y = position.y; y < position.y + 2*blastRadius; y++) {
      if (( x - midPos.x ) * ( x - midPos.x ) + ( y - midPos.y ) * ( y - midPos.y ) <= blastRadius * blastRadius) {
        game->getMap()->setPixel(x, y, 0);
      }
    }
  }

  game->getMap()->updateMap(position.x - 0.5*blastRadius, position.y - 0.5*blastRadius, 3*blastRadius, 3*blastRadius);
}

Bomb::Bomb(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  mass = 200;
  velocity.x = velocity.x / mass;
  velocity.y = -velocity.y / mass; // le sol est vers les +, le ciel vers les -

  blastRadius = 20;
  nBounces = 0;

  texture = new sf::Texture();
  sprite = new sf::Sprite();

  texture->loadFromFile("assets/bomb.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sf::Vector2f scale = sprite->getScale();
  sprite->setScale(scale.x * 0.5, scale.y * 0.5);

  // std::cout << "[DEBUG] BOMBE" << std::endl;
  // std::cout << "POSITION " << position.x << " " << position.y << std::endl;
  // std::cout << "VITESSE " << velocity.x << " " << velocity.y << std::endl;

}
Bomb::~Bomb() {}

Deagle::Deagle(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  mass = 100;
  velocity.x = velocity.x / mass;
  velocity.y = -velocity.y / mass; // le sol est vers les +, le ciel vers les -

  blastRadius = 10;
  nBounces = 0;

  texture = new sf::Texture();
  sprite = new sf::Sprite();

  texture->loadFromFile("assets/deagle.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sf::Vector2f scale = sprite->getScale();
  sprite->setScale(scale.x * 0.5, scale.y * 0.5);
}
Deagle::~Deagle() {}

Mine::Mine(sf::Vector2f pos, sf::Vector2f vel) {
  position = pos;
  velocity = vel;

  mass = 400;
  velocity.x = velocity.x / mass;
  velocity.y = -velocity.y / mass; // le sol est vers les +, le ciel vers les -

  blastRadius = 50;
  nBounces = 0;

  texture = new sf::Texture();
  sprite = new sf::Sprite();

  texture->loadFromFile("assets/mine.png");
  sprite->setTexture(*texture);
  sprite->setPosition(position);
  sf::Vector2f scale = sprite->getScale();
  sprite->setScale(scale.x * 0.5, scale.y * 0.5);
}
Mine::~Mine() {}

WeaponItem::WeaponItem(int c, int p) {
  count = c;
  payload = p;
}

Weapon * WeaponItem::generateWeapon(Game * game, Player * player) {
  Rob * rob = player->getControlledRob();
  sf::Vector2f pos = rob->getPosition();
  pos.x += rob->getAimVector().x * 3;
  pos.y += rob->getAimVector().y * 3;
  sf::Vector2f vel(rob->getStrength(), rob->getStrength());
  Weapon * current = nullptr;

  if (payload == 0) {
    std::cout << "[WARN] Pas d'arme sélectionnée! "<< std::endl;
  }
  else {
    player->setHasPlayed(true);
    if (payload == 1) {
      current = new Bomb(pos, vel);
    }
    if (payload == 2) {
      current = new Deagle(pos, vel);
    }
    if (payload == 3) {
      current = new Mine(pos, vel);
    }
    if (payload > 3) {
      std::cout << "[WARN] Arme sélectionnée non reconnue! "<< std::endl;
      player->setHasPlayed(false);
    }
  }
  return current;
}
