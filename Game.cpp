#include "Game.hpp"

Game::Game(sf::RenderWindow * wdw) {
  window = wdw;
  inGame = false;
}

Game::~Game() {
  removeEntities();
  removeGUIElements();

  delete terrain;
  delete bgimg;
  window->close();
}

void Game::update() {
  /*
  L'ordre compte :
  | | | | >o [caméra]
  \ \ \ \-- GUI (4)
   \ \ \--- Entités (3)
    \ \---- Terrain (2)
     \----- Img de fond (1)
  */
  window->clear();
  window->draw(*bgimg, sf::RenderStates::Default);

  if (inGame) {
    window->draw(*terrain, sf::RenderStates::Default);

    // // TODO : DESSIN DES ENTITES VIA CLASSE
    //  for (auto elt : entities) {
    //   // /!\ DEPLACEMENT ENTITES
    //   window->draw(*elt, sf::RenderStates::Default);
    // }
  }

  for (auto elt : gui) {
    window->draw(*elt, sf::RenderStates::Default);
  }

  for (auto elt : elements) {
    window->draw(*elt, sf::RenderStates::Default);
  }

  window->display();
}

bool Game::eventMgr(const sf::Vector2i& mousePos, sf::Event& evt) {
  // gestion chgt GUI
  if (!(window->pollEvent(evt))) {
    // Pas d'événement
    return true;
  }

  if (evt.type == sf::Event::Closed) {
      return false;
  }

  for (auto elt : gui) {
    elt->hoveredStatus(mousePos);
    if (elt->isHovered() && evt.type == sf::Event::MouseButtonPressed) {
      if (evt.mouseButton.button == sf::Mouse::Left) {
        elt->onClick();
      }
    }
  }
  // autre type de gestion d'event?
  return true;
}

void Game::addGUIElement(GUIElement * guielt) { gui.push_back(guielt); }
void Game::addGUIElement(std::vector<GUIElement *> guielts) {
  for (auto elt : guielts) {
    addGUIElement(elt);
  }
}
void Game::removeGUIElements() { gui.clear(); }
void Game::cleanGUIElements() {
  int i = 0;
  for (auto elt : gui) {
    if (!elt->isAlive()) {
      delete elt;
      gui.erase(gui.begin() + i);
    }
    i++;
  }
}

// void Game::addEntity(Entity * ety) { entities.push_back(ety); }
// void Game::addEntity(std::vector<Entity *> etys) {
//   for (auto elt : etys) {
//     addEntity(elt);
//   }
// }
// void Game::removeEntities() { entities.clear(); }
// void Game::cleanEntities() {
//   int i = 0;
//   for (auto elt : entities) {
//     if (false) { // /!\ CHECK VIE ENTITE
//       delete elt;
//       entities.erase(entities.begin() + i);
//     }
//     i++;
//   }
// }

void Game::addElement(sf::Sprite * elt) { elements.push_back(elt); }
void Game::addElement(std::vector<sf::Sprite *> elts) {
  for (auto elt : elts) {
    addElement(elt);
  }
}
void Game::removeElements() { elements.clear(); }

void Game::setMap(std::string path) {
  terrain = new Map(path);
}

void Game::setInGameStatus(bool value) {
  inGame = value;
}
