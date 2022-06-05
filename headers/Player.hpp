#ifndef PLY_HPP
#define PLY_HPP

#include "Rob.hpp"
#include "Weapons.hpp"

class Player {
  private:
    int id;

    std::vector<Rob *> squad;
    Rob * controlledRob;
    int controlledRobIndex;

    std::vector<WeaponItem *> arsenal;
    WeaponItem * selectedWeapon;
    int selectedWeaponIndex;

    sf::Clock actionCooldown;
    sf::Clock turnClock;

  public:
    Player(int i);
    ~Player();

    Rob * getControlledRob() { return controlledRob; }
    WeaponItem * getSelectedWeapon() { return selectedWeapon; }
    int const getNPlayable() const { return squad.size(); }

    void addEntity(Rob * ety);
    int const getId() { return id; }

    sf::Time const getActionCooldown() { return actionCooldown.getElapsedTime(); }
    sf::Time const getTurnClock() { return turnClock.getElapsedTime(); }

    void resetActionCooldown() { actionCooldown.restart(); }
    void resetTurnClock() { turnClock.restart(); }

};

#endif
