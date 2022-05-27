#include <unistd.h>

#include "Game.hpp"
#include "Button.hpp"

int main() {
  // initialisation
  bool playing = true;
  Map trn("test2.png");
  sf::RenderWindow wdw(sf::VideoMode(trn.getSize().x, trn.getSize().y), "RobS");
  sf::Texture bgtex;
  sf::Sprite bg;

  if (bgtex.loadFromFile("bg.png")) {
    bg.setTexture(bgtex);
  }
  else {
    std::cout << "Image de fond illisible."<< std::endl;
    bg.setColor(sf::Color::White);
  }

  Game * robs = new Game(&wdw, &trn, &bg);

  // éléments GUI
  sf::Font myFont;

  if (!myFont.loadFromFile("RetroGaming.ttf"))
  {
    std::cout << "Police d'écriture illisible."<< std::endl;
  }
  ChangeMenu * testCmdOne = new ChangeMenu();
  ChangeMenu * testCmdTwo = new ChangeMenu();

  Button testSpawn(sf::Vector2f(20, 20), sf::Vector2f(200, 50), "test", myFont, testCmdOne);
  Button testSpawnTwo(sf::Vector2f(100, 100), sf::Vector2f(200, 50), "test2", myFont, testCmdTwo);
  std::vector<GUIElement *> vecOne ; vecOne.push_back(&testSpawn);
  std::vector<GUIElement *> vecTwo ; vecTwo.push_back(&testSpawnTwo);
  testCmdOne->setTarget(robs);
  testCmdOne->setPayload(vecTwo);
  testCmdTwo->setTarget(robs);
  testCmdTwo->setPayload(vecOne);

  std::cout << "Initialisation terminée" << std::endl;

  robs->addGUIElement(&testSpawn);
  // boucle de jeu
  sf::Event evt;
  while (playing) {
    sf::Vector2i mouse = sf::Mouse::getPosition(wdw);

    playing = robs->eventMgr(mouse, evt);
    robs->update();
  }
}
