#include "headers/Game.hpp"

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RobS");
  brain = new GameLogic();
  inGame = false;
}

Game::~Game() {
  removeEntities();
  std::cout << "[CLEAN] Entités" << std::endl;
  removeGUIElements();
  std::cout << "[CLEAN] Éléments GUI" << std::endl;

  delete terrain;
  std::cout << "[CLEAN] Map" << std::endl;
  delete bgimg;
  std::cout << "[CLEAN] Image de fond" << std::endl;
  delete brain;
  std::cout << "[CLEAN] GameLogic" << std::endl;
  window->close();
  std::cout << "[CLEAN] Fenêtre" << std::endl;
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
  }

  for (auto elt : entities) {
    if (elt->isAlive()) {
      window->draw(*elt, sf::RenderStates::Default);
    }
  }

  for (auto elt : elements) {
    window->draw(*elt, sf::RenderStates::Default);
  }

  for (auto elt : gui) {
    if (elt->getActiveStatus() == true) {
      // pas de tracé pour les éléments HS
      window->draw(*elt, sf::RenderStates::Default);
    }
  }

  window->display();
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
      gui.erase(gui.begin() + i);
    }
    i++;
  }
}

bool Game::isAnythingHovered() {
  for (auto elt : gui) {
    if (elt->isHovered()) {
      return true;
    }
  }
  return false;
}

void Game::addEntity(Entity * ety) { entities.push_back(ety); }
void Game::addEntity(std::vector<Entity *> etys) {
  for (auto elt : etys) {
    addEntity(elt);
  }
}
void Game::removeEntities() { entities.clear(); }

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
