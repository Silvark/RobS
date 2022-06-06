#include "headers/Player.hpp"

Player::Player(int i) {
  id = i;

  controlledRob = nullptr;
  controlledRobIndex = -1;

  selectedWeapon = nullptr;
  selectedWeaponIndex = -1;

  WeaponItem * bombs = new WeaponItem(99, 0);
  WeaponItem * deagle = new WeaponItem(99, 1);
  WeaponItem * mines = new WeaponItem(99, 2);

  arsenal.push_back(bombs);
  arsenal.push_back(deagle);
  arsenal.push_back(mines);
}

Player::~Player() {
  arsenal.clear();
  squad.clear();
}

void Player::nextControlledRob() {
  if (controlledRobIndex == -1) {
     if (squad.size() > 0) {
       controlledRobIndex = 0;
     }
     else {
       return;
     }
  }
  else {
    controlledRob->setControlledStatus(false);
    controlledRobIndex += 1;
    if (controlledRobIndex > squad.size()) {
      controlledRobIndex = 0;
    }
  }
  controlledRob = squad[controlledRobIndex];
  controlledRob->setControlledStatus(true);
}

void Player::prevControlledRob() {
  if (controlledRobIndex == -1) {
     if (squad.size() > 0) {
       controlledRobIndex = 0;
     }
     else {
       return;
     }
  }
  else {
    controlledRob->setControlledStatus(false);
    controlledRobIndex -= 1;
    if (controlledRobIndex < 0) {
      controlledRobIndex = squad.size() - 1;
    }
  }
  controlledRob = squad[controlledRobIndex];
  controlledRob->setControlledStatus(true);
}

void Player::addEntity(Rob * ety) {
  squad.push_back(ety);
}
