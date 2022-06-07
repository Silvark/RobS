#ifndef ROB_HPP
#define ROB_HPP

#include "Entity.hpp"
class Game;

class Rob : public Entity {
  private:
    sf::Vector2f aimVector;
    float strength;

    int health;
    int energy;

    sf::Texture * selectorTexture;
    sf::Sprite * selectorSprite;

  public:
    Rob(sf::Vector2f pos, sf::Vector2f vel, int type);
    ~Rob();

    int const getHealth() const { return health; }
    void setHealth(int value) { health = value; }

    int const getEnergy() const { return energy; }
    void setEnergy(int value) { energy = value; }

    float const getStrength() const { return strength; }
    sf::Vector2f const getAimVector() const { return aimVector; }

    void calculateAimVector(sf::Vector2i mousePos);

    void move(Game * game);
    void onCollision(Game * game);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
