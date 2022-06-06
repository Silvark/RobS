#include "headers/Game.hpp"
#include "headers/GameLogic.hpp"

GameLogic::GameLogic() {
  one = new Player(1);
  two = new Player(2);
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

void GameLogic::changeWeapon(Player * player) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    player->setSelectedWeapon(0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    player->setSelectedWeapon(1);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
    player->setSelectedWeapon(2);
  }
}

void GameLogic::placeRob(sf::Vector2f position, Game * game, Player * owner) {
  if (owner->getActionCooldown() < sf::seconds(0.3)) {
    return;
  }

  Map * terrain = game->getMap();
  bool validPlacement = true;

  try {
    for (size_t xPix = position.x; xPix < position.x + 19; xPix++) {
      for (size_t yPix = position.y; yPix < position.y + 41; yPix++) {
        if (terrain->getPixel(xPix, yPix) == true) {
          validPlacement = false;
        }
      }
    }
  }
  catch (const std::invalid_argument& except) {
    // bord de map
    validPlacement = false;
  }

  if (!validPlacement) {
    std::cout << "[WARN] Placement invalide" << std::endl;
    return;
  }

  sf::Vector2f vel(0, 0);
  Rob * newMember = new Rob(position, vel, owner->getId());

  game->addEntity(newMember);
  owner->addEntity(newMember);

  std::cout << "[INFO] Rob placé en (" << position.x << ", " << position.y << ")" << std::endl;
  owner->resetActionCooldown();
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
      if (game->getInGameStatus() == true) {
        fsm = 1;
      }
      break;

    case 1: // début de partie
      // MaJ GUI [placement de robs] (pas de GUI)
      std::cout << "[INFO] Partie lancée!" << std::endl;
      std::cout << "[INFO] Joueur 1, placez vos RobS!" << std::endl;

      // TODO : indiquer qu'il faut placer des joueurs
      // le terminal fait l'affaire, en vrai

      fsm = 11;
      break;

    case 11: // j1 pose ses robs
      // case 11 tant que le nombre de joueurs placés (donc dans one->playable) n'est pas 5
      if (one->getNPlayable() >= 5) {
        fsm = 12;
        std::cout << "[INFO] Joueur 2, placez vos RobS!" << std::endl;
      }

      if (events.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f pos(mousePos.x, mousePos.y);
        placeRob(pos, game, one);
      }

      break;

    case 12: // j2 pose ses robs
      // case 12 tant que le nombre de joueurs placés (donc dans two->playable) n'est pas 5
      if (two->getNPlayable() >= 5) {
        fsm = 2;
        std::cout << "[INFO] Début de la partie!" << std::endl;
      }

      if (events.mouseButton.button == sf::Mouse::Left) {
        // check de la zone autour du click pour voir si on peut accueillir un rob
        sf::Vector2f pos(mousePos.x, mousePos.y);
        placeRob(pos, game, two);
      }
      break;

    case 2: // partie en cours
      // MaJ GUI [combat]
      {
      Inventory * inv = new Inventory(sf::Vector2f((1280/2)-200, 0), one);
      game->removeGUIElements();
      game->addGUIElement(inv);
      fsm = 21;
      }
      break;

    case 21: // j1 joue
      // case 21 tant que one n'a pas joué et peut encore jouer (tour de 25s)
      changeWeapon(one); // regarde si on change d'arme et agit en csq

      break;

    case 22: // j2 joue
      // case 22 tant que one n'a pas joué et peut encore jouer (tour de 25s)
      changeWeapon(two); // regarde si on change d'arme et agit en csq

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

void GameLogic::physicsMgr(Game * game) {
  std::vector<Entity *> entities = game->getEntities();
  for (auto elt : entities) {
    (*elt)->move(game);
  }

}
