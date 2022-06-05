#ifndef ROB_HPP
#define ROB_HPP

#include "Entity.hpp"

class Rob : public Entity {
  private:
    sf::Vector2f aimVector;
    float strength;

    int health;
    int energy;

    bool isControlled;

  public:
    Rob(sf::Vector2f pos, sf::Vector2f vel, int type);
    ~Rob();

    int const getHealth() const { return health; }
    void setHealth(int value) { health = value; }

    int const getEnergy() const { return energy; }
    void setEnergy(int value) { energy = value; }

    sf::Vector2f calculateAimVector(sf::Vector2i& mousePos);
    float calculateStrength(sf::Vector2i& mousePos);

    void move();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
