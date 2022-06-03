#include "GameLogic.hpp"
#include "Game.hpp"

GameLogic::GameLogic() {
  one = new Player();
  two = new Player();
}

GameLogic::~GameLogic() {
  delete one;
  delete two;
}

void GameLogic::setControlTarget(Rob * playable) {
  controlTarget = playable;
}

Rob * const GameLogic::getControlTarget() const {
  return controlTarget;
}


void GameLogic::eventMgr(Game * game, const sf::Vector2i& mousePos) {
  // Guard clause : y'a t-il des événements?
  if (!(game->window->pollEvent(events))) {
    return;
  }

  // jeu fermé
  if (events.type == sf::Event::Closed) {
    fsm = 99;
    return;
  }

  // détection interactions GUI
  for (auto guiElt : game->gui) {
    guiElt->hoveredStatus(mousePos);
    if (guiElt->isHovered() && events.type == sf::Event::MouseButtonPressed) {
      if (events.mouseButton.button == sf::Mouse::Left) {
        guiElt->onClick();
      }
    }
  }

  switch (fsm) {
    case 0: // menu principal

      break;
    case 1: // début de partie

      break;
    case 11: // j1 pose ses robs

      break;
    case 12: // j2 pose ses robs

      break;
    case 2: // partie en cours

      break;
    case 21: // j1 joue

      break;
    case 22: //j2 joue

      break;
    case 3: // partie terminée

      break;
    case 31: // j1 gagne

      break;
    case 32: // j2 gagne

      break;
    default:
      std::cout << "Soit le jeu s'est arrêté, soit on a un comportement inattendu" << std::endl;
      break;
  }
  return;
}
