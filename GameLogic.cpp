#include "GameLogic.hpp"
#include "Game.hpp"

GameLogic::GameLogic() {
  one = new Player();
  two = new Player();
  fsm = 0;
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

Rob * placeRob(sf::Vector2f position, Player * owner) {

}

int const GameLogic::getFSM() {
  return fsm;
}

void GameLogic::eventMgr(Game * game, const sf::Vector2i& mousePos) {
  // Guard clause : y'a t-il des événements?
  if (!(game->getWindow()->pollEvent(events))) {
    return;
  }

  // jeu fermé?
  if (events.type == sf::Event::Closed) {
    fsm = 99;
    return;
  }

  // détection interactions GUI
  for (auto guiElt : *(game->getGUI())) {
    guiElt->hoveredStatus(mousePos);
    if (guiElt->isHovered() && events.type == sf::Event::MouseButtonPressed) {
      if (events.mouseButton.button == sf::Mouse::Left) {
        guiElt->onClick();
      }
    }
  }

  switch (fsm) {
    case 0: // menu principal & intro
      if (robs->getInGameStatus() == true) {
        fsm = 1;
      }

    case 1: // début de partie
      // MaJ GUI [placement de robs]


      fsm = 11;
    case 11: // j1 pose ses robs
      // case 11 tant que le nombre de joueurs placés (donc dans one->playable) n'est pas 5

      break;
    case 12: // j2 pose ses robs
      // case 12 tant que le nombre de joueurs placés (donc dans two->playable) n'est pas 5

      break;
    case 2: // partie en cours
      // MaJ GUI [combat]
      robs->removeGUIElements();

      break;
    case 21: // j1 joue
      // case 21 tant que one n'a pas joué et peut encore jouer (tour de 25s)

      break;
    case 22: // j2 joue
      // case 22 tant que one n'a pas joué et peut encore jouer (tour de 25s)

      break;
    case 3: // partie terminée

      break;
    case 31: // j1 gagne

      break;
    case 32: // j2 gagne

      break;
    default:
      std::cout << "[WARN] Comportement inattendu" << std::endl;
      break;
  }
  return;
}
