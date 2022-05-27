#include "Game.hpp"
#include "GUIElement.hpp"
#include "Commands.hpp"

void ChangeMenu::setTarget(Game * instance) {
  game = instance;
}
void ChangeMenu::setPayload(std::vector<GUIElement *> menu) {
  elements = menu;
}
void ChangeMenu::execute() {
  game->removeGUIElements();
  game->addGUIElement(elements);
}
