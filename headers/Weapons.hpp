#ifndef WPN_HPP
#define WPN_HPP

#include "Entity.hpp"

class Weapon : public Entity {
  private:
    int mass;
    int nBounces;

  public:
    void move();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class WeaponItem {
  private:
    int count;
    Weapon * weapon;

  public:
};

#endif
