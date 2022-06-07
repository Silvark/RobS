#include "headers/Game.hpp"
#include "headers/Rob.hpp"

Rob::Rob(sf::Vector2f pos, sf::Vector2f vel, int type) {
  position = pos;
  velocity = vel;

  health = 100;
  energy = 100;

  mass = 10;

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
  std::cout << "dtor rob" << '\n';
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
  if (position.y < -50 || position.y > game->getMap()->getSize().y + 50
  ||  position.x < -50 || position.y > game->getMap()->getSize().x + 50)
  { alive = false; return; }

  Map * terrain = game->getMap();
  sf::FloatRect dims = sprite->getLocalBounds();
  bool colTL, colTR, colBL, colBR;
  position.y -= GRAVITY/1e4;

  sf::Vector2f finalPos = position + velocity; // velocity est en unités de déplacement
  sf::Vector2f interPos;

  float resolution = 0.1;
  for (float increment = 0; increment <= 1; increment = increment + resolution) {
    interPos.x = (velocity.x * increment) + position.x;
    interPos.y = (velocity.y * increment) + position.y;

    // check coin sup gauche
    try {
    colTL = terrain->getPixel(floor(interPos.x) + 1, floor(interPos.y) + 1)
            && terrain->getPixel(ceil(interPos.x) + 1, ceil(interPos.y) + 1);
    }

    catch (const std::invalid_argument& except) {
      // out of bounds
      alive = false;
      return;
    }
    // check coin sup droit
    try {
    colTR = terrain->getPixel(floor(interPos.x + dims.width) - 1, floor(interPos.y) + 1)
            && terrain->getPixel(ceil(interPos.x + dims.width) - 1, ceil(interPos.y) + 1);
    }

    catch (const std::invalid_argument& except) {
      // out of bounds
      alive = false;
      return;
    }

    // check coin inf gauche
    try {
    colBL = terrain->getPixel(floor(interPos.x) + 1, floor(interPos.y + dims.height) - 1)
            && terrain->getPixel(ceil(interPos.x) + 1, ceil(interPos.y + dims.height) - 1);
    }

    catch (const std::invalid_argument& except) {
      // out of bounds
      alive = false;
      return;
    }

    // check coin inf droit
    try {
    colBR = terrain->getPixel(floor(interPos.x + dims.width) - 1, floor(interPos.y + dims.height) - 1)
            && terrain->getPixel(ceil(interPos.x + dims.width) - 1, ceil(interPos.y + dims.height) - 1);
    }

    catch (const std::invalid_argument& except) {
      // out of bounds
      alive = false;
      return;
    }

    if (colBL || colBR || colTL || colTR ) {
      // collision qq part
      interPos.x -= (velocity.x * increment);
      interPos.y -= (velocity.y * increment);
      onCollision(game);
      break;
    }
  }
  position = interPos;
}

void Rob::onCollision(Game * game) {
  velocity.x = 0;
  velocity.y = 0;
  midAir = false;
  return;
}

void Rob::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (!alive) {
    return;
  }

  sprite->setPosition(position);
  target.draw(*sprite, states);
  if (isControlled) {
    selectorSprite->setPosition(sf::Vector2f(position.x, position.y - 20));
    target.draw(*selectorSprite, states);
  }
}
