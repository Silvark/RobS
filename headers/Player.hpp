#ifndef PLY_HPP
#define PLY_HPP

#include "Rob.hpp"
#include "Weapons.hpp"

class Inventory;

class Player {
  private:
    int id;
    bool hasPlayed;

    std::vector<Rob *> squad;
    Rob * controlledRob;
    int controlledRobIndex;

    std::vector<WeaponItem *> arsenal;
    WeaponItem * selectedWeapon;
    int selectedWeaponIndex;

    Inventory * inv;

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
    bool const getHasPlayed() { return hasPlayed; }
    Inventory * const getInventory() { return inv; }

    void addEntity(Rob * ety);

    Rob * nextControlledRob();
    Rob * prevControlledRob();

    void resetActionCooldown() { actionCooldown.restart(); }
    void resetTurnClock() { turnClock.restart(); }

    void setHasPlayed(bool value) { hasPlayed = value; }
    void setSelectedWeapon(int value);


};

#endif
