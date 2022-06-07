#include "headers/Game.hpp"

Game::Game() {
  window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RobS");
  brain = new GameLogic();
  inGame = false;
}

Game::~Game() {
  std::cout << "dtor game" << '\n';
  delete terrain;
  delete brain;
  delete bgimg;

  std::cout << "destroying gui elements" << '\n';
  for (auto elt : gui) {
    delete elt;
  }

  std::cout << "destroying entities" << '\n';
  for (auto elt : entities) {
    delete elt;
  }

  std::cerr << "destroying other elements" << '\n';
  for (auto elt : elements) {
    delete elt;
  }

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
    if (elt->getActiveStatus() == true && elt->isAlive() == true) {
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
void Game::removeGUIElements() {
  for (auto elt : gui) {
    elt->aliveStatus(false);
    elt->setActiveStatus(false);
  }
}

void Game::addEntity(Entity * ety) { entities.push_back(ety); }
void Game::addEntity(std::vector<Entity *> etys) {
  for (auto elt : etys) {
    addEntity(elt);
  }
}
void Game::removeEntities() {
  for (auto elt : entities) {
    elt->aliveStatus(false);
  }
}

void Game::addElement(sf::Sprite * elt) { elements.push_back(elt); }
void Game::addElement(std::vector<sf::Sprite *> elts) {
  for (auto elt : elts) {
    addElement(elt);
  }
}
void Game::removeElements() {
  for (auto elt : elements) {
    elt->setColor(sf::Color::Transparent);
  }
}

void Game::setMap(std::string path) {
  terrain = new Map(path);
}

void Game::setInGameStatus(bool value) {
  inGame = value;
}
