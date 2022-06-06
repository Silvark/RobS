#include "headers/Game.hpp"
#include "headers/Commands.hpp"

ChangeMenu::ChangeMenu(Game * istc, std::vector<GUIElement *> * gelts, std::vector<sf::Sprite *> * elts) {
  game = istc;
  guielements = gelts;
  elements = elts;
}

void ChangeMenu::setTarget(Game * instance) {
  game = instance;
}
void ChangeMenu::setPayload(std::vector<GUIElement *> * gelts, std::vector<sf::Sprite *> * elts) {
  guielements = gelts;
  elements = elts;
}
void ChangeMenu::execute() {
  game->removeGUIElements();
  game->addGUIElement(*guielements);
  game->removeElements();
  game->addElement(*elements);
}

SetMap::SetMap(Game * istc, std::string path) {
  game = istc;
  pathToMap = path;
}

void SetMap::execute() {
  game->setMap(pathToMap);
  std::cout << "[INFO] Map changée! (" << pathToMap << ")" << std::endl;
}

LaunchGame::LaunchGame(Game * istc, sf::Sprite * bg) {
  game = istc;
  background = bg;
}

void LaunchGame::execute() {
  game->setInGameStatus(true);
  game->setBackground(background);
  game->removeGUIElements();
  game->removeElements();
}
