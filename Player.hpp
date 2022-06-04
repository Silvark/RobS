#ifndef PLY_HPP
#define PLY_HPP

#include "Rob.hpp"
#include "Weapons.hpp"

class Player {
  private:
    std::vector<Rob *> playable;
    std::vector<Weapon *> ammo;

  public:
    Player();
    ~Player();

};

#endif
