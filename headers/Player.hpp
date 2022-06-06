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
    int const getId() { return id; }
    int const getSelectedWeaponIndex() { return selectedWeaponIndex; }
    sf::Time const getActionCooldown() { return actionCooldown.getElapsedTime(); }
    sf::Time const getTurnClock() { return turnClock.getElapsedTime(); }

    void addEntity(Rob * ety);
    void setSelectedWeapon(int value) { selectedWeaponIndex = value; selectedWeapon = arsenal[selectedWeaponIndex]; }
    void nextControlledRob();
    void prevControlledRob();

    void resetActionCooldown() { actionCooldown.restart(); }
    void resetTurnClock() { turnClock.restart(); }

};

#endif
