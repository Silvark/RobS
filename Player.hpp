#ifndef PLY_HPP
#define PLY_HPP

#include "Entity.hpp"

class Player : public Entity {
  public:
    int const getHealth() { return health; }
    int const getEnergy() { return energy; }

    void setHealth(int value) { health = value; }
    void setEnergy(int value) { energy = value; }

    void move();
};

#endif
