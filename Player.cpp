#include "headers/GUIElements.hpp"
#include "headers/Player.hpp"

Player::Player(int i) {
  id = i;

  controlledRob = nullptr;
  controlledRobIndex = -1;

  selectedWeapon = nullptr;
  selectedWeaponIndex = -1;

  WeaponItem * bombs = new WeaponItem(999, 1);
  WeaponItem * deagle = new WeaponItem(999, 2);
  WeaponItem * mines = new WeaponItem(999, 3);

  inv = new Inventory(sf::Vector2f((1280/2)-200, 0));

  arsenal.push_back(bombs);
  arsenal.push_back(deagle);
  arsenal.push_back(mines);
}

Player::~Player() {
  std::cout << "dtor player" << '\n';
  arsenal.clear();
}

Rob * Player::nextControlledRob() {
  for (auto rob : squad) {
    rob->setControlledStatus(false);
  }

  if (controlledRobIndex == -1) {
    // premier switch
    controlledRobIndex = 0;
    controlledRob = squad[controlledRobIndex];
  }
  else {
    do {
      controlledRobIndex += 1;
      if (controlledRobIndex > squad.size() - 1) {
        controlledRobIndex = 0;
      }
      controlledRob = squad[controlledRobIndex];
    } while (controlledRob->isAlive() == false);
  }
  controlledRob->setControlledStatus(true);
  return controlledRob;
}

void Player::setSelectedWeapon(int value) {
  selectedWeaponIndex = value;
  selectedWeapon = arsenal[selectedWeaponIndex-1];
}

Rob * Player::prevControlledRob() {
  for (auto rob : squad) {
    rob->setControlledStatus(false);
  }

  if (controlledRobIndex == -1) {
    // premier switch
    controlledRobIndex = 0;
    controlledRob = squad[controlledRobIndex];
  }
  else {
    do {
      controlledRobIndex -= 1;
      if (controlledRobIndex < 0) {
        controlledRobIndex = squad.size() - 1;
      }
      controlledRob = squad[controlledRobIndex];
    } while (controlledRob->isAlive() == false);
  }
  controlledRob->setControlledStatus(true);
  return controlledRob;
}

void Player::addEntity(Rob * ety) {
  squad.push_back(ety);
}
