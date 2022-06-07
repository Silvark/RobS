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
    player->getInventory()->updateSelected(1); // maj graphique
    player->getInventory()->setSelectedSlot(1); // suivi sur la structure inv.
    player->setSelectedWeapon(1); // sélection arme concrète
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    player->getInventory()->updateSelected(2); // maj graphique
    player->getInventory()->setSelectedSlot(2); // suivi sur la structure inv.
    player->setSelectedWeapon(2); // sélection arme concrète
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
    player->getInventory()->updateSelected(3); // maj graphique
    player->getInventory()->setSelectedSlot(3); // suivi sur la structure inv.
    player->setSelectedWeapon(3); // sélection arme concrète
  }
  else {
    player->setSelectedWeapon(player->getInventory()->getSelectedSlot()); // update via click
  }
}

void GameLogic::changeRob(Player * player) {
  Rob * controlRecipient;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    controlRecipient = player->prevControlledRob();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    controlRecipient = player->nextControlledRob();
  }
  setControlTarget(controlRecipient);
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

void GameLogic::moveRob(Player * player) {
  Rob * controlRecipient = player->getControlledRob();
  sf::Vector2f vel = controlRecipient->getAimVector();
  float mult = controlRecipient->getStrength();
  sf::Vector2f mov(0, 0);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    mov.x -= 0.01;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    mov.x += 0.01;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    std::cout << "[DEBUG] Saut!" << '\n';
    mov = vel;
    mov.x *= mult;
    mov.y *= mult;
  }
  controlRecipient->updateVelocity(mov);
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
      // init gui jeu
      game->removeGUIElements();
      game->addGUIElement(one->getInventory());
      game->addGUIElement(two->getInventory());

      // mettre le bon inventaire
      one->getInventory()->setActiveStatus(true);
      two->getInventory()->setActiveStatus(false);

      // init indicateurs
      one->nextControlledRob();
      two->nextControlledRob();

      fsm = 21;
      one->resetTurnClock();
      one->setHasPlayed(false);
      }
      break;

    case 21: // j1 joue
      // case 21 tant que one n'a pas joué et peut encore jouer (tour de 30s)
      if (one->getTurnClock() > sf::seconds(30)) {
        std::cout << "[INFO] Fin du tour du joueur 1!\nCause : timeout" << std::endl;
        fsm = 22;

        // mettre le bon inventaire
        one->getInventory()->setActiveStatus(false);
        two->getInventory()->setActiveStatus(true);
        two->resetTurnClock();
        two->resetActionCooldown();
        two->setHasPlayed(false);
      }

      one->getControlledRob()->calculateAimVector(mousePos);
      changeRob(one);
      changeWeapon(one);
      moveRob(one);

      if (events.mouseButton.button == sf::Mouse::Left && one->getActionCooldown() > sf::seconds(0.3)) {
        if (game->isAnythingHovered()) {
          // click pris en compte par GUI
          break;
        }

        Weapon * current = one->getSelectedWeapon()->generateWeapon(game, one);
        if (current && one->getHasPlayed() == true) {
          game->addEntity(current);
          std::cout << "[INFO] Fin du tour du joueur 1!\nCause : a joué" << std::endl;
          fsm = 22;

          // mettre le bon inventaire
          one->getInventory()->setActiveStatus(false);
          two->getInventory()->setActiveStatus(true);
          two->resetTurnClock();
          two->resetActionCooldown();
          two->setHasPlayed(false);
        }
      }

      break;

    case 22: // j2 joue
      // case 22 tant que two n'a pas joué et peut encore jouer (tour de 30s)
      if (two->getTurnClock() > sf::seconds(30)) {
        std::cout << "[INFO] Fin du tour du joueur 2!\nCause : timeout" << std::endl;
        fsm = 21;

        // mettre le bon inventaire
        two->getInventory()->setActiveStatus(false);
        one->getInventory()->setActiveStatus(true);
        one->resetTurnClock();
        one->resetActionCooldown();
        one->setHasPlayed(false);
      }

      two->getControlledRob()->calculateAimVector(mousePos);
      changeRob(two);
      changeWeapon(two);
      moveRob(two);

      if (events.mouseButton.button == sf::Mouse::Left && two->getActionCooldown() > sf::seconds(0.3)) {
        if (game->isAnythingHovered()) {
          // click pris en compte par GUI
          break;
        }

        Weapon * current = two->getSelectedWeapon()->generateWeapon(game, two);
        if (current && two->getHasPlayed() == true) {
          game->addEntity(current);
          std::cout << "[INFO] Fin du tour du joueur 2!\nCause : a joué" << std::endl;
          fsm = 21;

          // mettre le bon inventaire
          two->getInventory()->setActiveStatus(false);
          one->getInventory()->setActiveStatus(true);
          one->resetTurnClock();
          one->resetActionCooldown();
          one->setHasPlayed(false);
        }
      }

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
  std::vector<Entity *> * entities = game->getEntities();
  for (auto elt : *entities) {
    if (elt->isAlive()) {
      // pas de simulation pour les éléments HS
      elt->updateVelocity();
      elt->move(game);
    }
  }
}
