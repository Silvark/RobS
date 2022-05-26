#include "Game.hpp"

Game::Game(sf::RenderWindow * wdw, Map * trn, sf::Texture * bg) {
  window = wdw;
  terrain = trn;
  bgimg = bg;
}

Game::~Game() {
  removeEntities()
  removeGUIElements()

  delete terrain;
  delete bgimg;
  window.close()
}

void Game::update() {
  bgimg->draw(window, sf::RenderStates::Default);
  terrain->draw(window, sf::RenderStates::Default);
  for (auto elt : entities) {
    // /!\ DEPLACEMENT ENTITES
    elt->draw(window, sf::RenderStates::Default);
  }

  for (auto elt : gui) {
    elt->hoveredStatus();
    elt->draw(window, sf::RenderStates::Default);
  }
}

void Game::addEntity(Entity * ety) { entities.push_back(ety); }
void Game::addGUIElement(GUIElement * guielt) { gui.push_back(guielt); }

void Game::addEntity(std::vector<Entity *> etys) {
  for (auto elt : etys) {
    addEntity(elt);
  }
}

void Game::addGUIElement(std::vector<GUIElement *> guielts) {
  for (auto elt : guielts) {
    addGUIElement(elt);
  }
}

void Game::removeEntities() { entities.clear(); }
void Game::removeGUIElements() { gui.clear(); }

void Game::cleanEntities() {
  int i = 0;
  for (auto elt : entities) {
    if (false) { // /!\ CHECK VIE ENTITE
      delete elt;
      entities.erase(i);
    }
    i++;
  }
}

void Game::cleanGUIElements() {
  int i = 0;
  for (auto elt : guielts) {
    if (!elt->isAlive()) {
      delete elt;
      guielts.erase(i);
    }
    i++;
  }
}
