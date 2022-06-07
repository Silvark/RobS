#include "headers/Game.hpp"
#include "headers/Rob.hpp"

Rob::Rob(sf::Vector2f pos, sf::Vector2f vel, int type) {
  position = pos;
  velocity = vel;

  health = 100;
  energy = 100;

  mass = 1;

  isControlled = false;
  strength = 0;
  aimVector = sf::Vector2f(0, 0);

  texture = new sf::Texture();
  sprite = new sf::Sprite();

  selectorTexture = new sf::Texture();
  selectorSprite = new sf::Sprite();
  selectorTexture->loadFromFile("assets/pointer.png");
  selectorSprite->setTexture(*selectorTexture);
  selectorSprite->setPosition(sf::Vector2f(position.x, position.y));

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

void Rob::calculateAimVector(sf::Vector2i mousePos) {
  sf::Vector2f midPoint(position.x + sprite->getLocalBounds().width/2,
                        position.y - sprite->getLocalBounds().height/2);
  float dist;

  aimVector.x = mousePos.x - midPoint.x;
  aimVector.y = mousePos.y - midPoint.y;

  dist = std::sqrt((aimVector.x * aimVector.x) + (aimVector.y * aimVector.y));
  aimVector.x = aimVector.x/dist; // vecteur unitaire
  aimVector.y = aimVector.y/dist; // vecteur unitaire

  strength = dist/(1280*3);
}

void Rob::move(Game * game) {
  Map * terrain = game->getMap();
  bool collides = false;

  sf::Vector2f initialPosition = this->getPosition();
  sf::Vector2f finalPosition;
  sf::Vector2f displacement;
  sf::FloatRect collidePoint = sprite->getLocalBounds();

  initialPosition.x += collidePoint.width/2;
  initialPosition.y += collidePoint.height;

  finalPosition.x = initialPosition.x + velocity.x;
  finalPosition.y = initialPosition.y + velocity.y;

  displacement.x = finalPosition.x - initialPosition.x;
  displacement.y = finalPosition.y - initialPosition.y;

  sf::Vector2f intermediatePosition;
  float resolution = 0.01;

  for (float increment = 0; increment < 1; increment = increment + resolution) {
    intermediatePosition.x = initialPosition.x + displacement.x * increment;
    intermediatePosition.y = initialPosition.y + displacement.y * increment;

    try {
    collides = terrain->getPixel(floor(intermediatePosition.x), floor(intermediatePosition.y))
    && terrain->getPixel(ceil(intermediatePosition.x), ceil(intermediatePosition.y));
    }
    catch (const std::invalid_argument& except) {
      // oob
      std::cout << "[WARN] Entité hors de la map!" << std::endl;
      collides = false;
      alive = false;
      return;
    }

    if (collides) {
      intermediatePosition.x -= collidePoint.width/2;
      intermediatePosition.y -= collidePoint.height;
      this->setPosition(intermediatePosition);
      onCollision(game);
      return;
    }
  }

  finalPosition.x -= collidePoint.width/2;
  finalPosition.y -= collidePoint.height;
  this->setPosition(finalPosition);
  return;
}

void Rob::onCollision(Game * game) {
  velocity.x = 0;
  velocity.y = 0;
}

void Rob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!alive) {
    return;
  }

  sprite->setPosition(position);
  selectorSprite->setPosition(sf::Vector2f(position.x, position.y - 20));
  target.draw(*sprite, states);
  if (isControlled) {
    // TODO : dessiner la flèche qui indique où on tire
    target.draw(*selectorSprite, states);
  }
}
