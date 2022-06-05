#include "Player.hpp"

Player::Player(int i) {
  id = i;

  controlledRob = nullptr;
  controlledRobIndex = -1;

  selectedWeapon = nullptr;
  selectedWeaponIndex = -1;
}

Player::~Player() {

}

void Player::addEntity(Rob * ety) {
  squad.push_back(ety);
}
