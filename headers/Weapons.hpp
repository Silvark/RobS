#ifndef WPN_HPP
#define WPN_HPP

#include "Entity.hpp"
class Player;
class Game;

class Weapon : public Entity {
  protected:
    int nBounces;
    int blastRadius;

  public:
    Weapon();
    Weapon(sf::Vector2f pos, sf::Vector2f vel);
    ~Weapon() {}

    void move(Game * game);
    void onCollision(Game * game);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void explode(Game * game);
};

class Bomb : public Weapon {
  public:
    Bomb(sf::Vector2f pos, sf::Vector2f vel);
    ~Bomb();
};

class Deagle : public Weapon {
  public:
    Deagle(sf::Vector2f pos, sf::Vector2f vel);
    ~Deagle();
};

class Mine : public Weapon {
  public:
    Mine(sf::Vector2f pos, sf::Vector2f vel);
    ~Mine();
};

class WeaponItem {
  private:
    int count;
    int payload;

  public:
    WeaponItem(int c, int p);
    ~WeaponItem();
    Weapon * generateWeapon(Game * game, Player * player);
};

#endif
