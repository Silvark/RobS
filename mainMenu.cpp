#include <unistd.h>
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "Button.hpp"

sf::Sprite * spriteFromTexture(sf::Texture * texture, bool setOriginToMiddle, float scale) {
  sf::Sprite * sprite = new sf::Sprite();
  sprite->setTexture(*texture);

  if (setOriginToMiddle) {
  sprite->setOrigin(sprite->getLocalBounds().width/2,
                    sprite->getLocalBounds().height/2);
  }
  sprite->setScale(scale, scale);
  return sprite;
}

int main() {
  // Initialisation globale
  /// Jeu
  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RobS");

  sf::Font myFont;
  if (!myFont.loadFromFile("RetroGaming.ttf")) {
    std::cout << "Police d'écriture illisible."<< std::endl;
  }

  /// Textures
  sf::Texture bgimg_tex; bgimg_tex.loadFromFile("assets/bg.png");
  sf::Texture map01_tex; map01_tex.loadFromFile("assets/map01.png");
  sf::Texture map02_tex; map02_tex.loadFromFile("assets/map02.png");
  sf::Texture robslogo_tex; robslogo_tex.loadFromFile("assets/robs.png");
  sf::Texture introOne_tex; introOne_tex.loadFromFile("assets/kartemer.png");
  sf::Texture introTwo_tex; introTwo_tex.loadFromFile("assets/battle.png");

  Game * robs = new Game(window);

  // Main Menu
  /// Initialisation
  //// Background
  sf::Sprite * bgSprite = spriteFromTexture(&bgimg_tex, false, 1);
  robs->setBackground(bgSprite);

  //// Logo
  sf::Sprite * robsLogo = spriteFromTexture(&robslogo_tex, true, 1);
  robsLogo->setPosition(1280/2, 720*0.3);
  robs->addElement(robsLogo);

  //// Btn "Jouer"
  std::vector<sf::Sprite *> * mapSelImgs = new std::vector<sf::Sprite *>;
  std::vector<GUIElement *> * mapSelBtns = new std::vector<GUIElement *>;
  ChangeMenu * toMapSel = new ChangeMenu(robs, mapSelBtns, mapSelImgs);
  Button * btnToMapSel = new Button(sf::Vector2f(1280/2 - 230, 720*0.75), sf::Vector2f(460, 50), "Jouer!", myFont, toMapSel);
  robs->addGUIElement(btnToMapSel);

  // Map Selection
  /// Btns chgt map
  SetMap * changeToMapone = new SetMap(robs, "assets/map01.png");
  SetMap * changeToMaptwo = new SetMap(robs, "assets/map02.png");
  LaunchGame * toGame = new LaunchGame(robs);
  Button * btnSelMapone = new Button(sf::Vector2f(1280*0.12, 720*0.6), sf::Vector2f(460, 50), "Minecraft Cave", myFont, changeToMapone);
  Button * btnSelMaptwo = new Button(sf::Vector2f(1280*0.52, 720*0.6), sf::Vector2f(460, 50), "King of the Hill", myFont, changeToMaptwo);
  Button * btnToGame = new Button(sf::Vector2f(1280/2 - 260, 720*0.75), sf::Vector2f(540, 50), "Jouer!", myFont, toGame);
  mapSelBtns->push_back(btnSelMapone);
  mapSelBtns->push_back(btnSelMaptwo);
  mapSelBtns->push_back(btnToGame);

  // Affichage maps
  sf::Sprite * mapone = spriteFromTexture(&map01_tex, true, 0.36);
  sf::Sprite * maptwo = spriteFromTexture(&map02_tex, true, 0.36);
  mapone->setPosition(1280*0.3, 720*0.4);
  maptwo->setPosition(1280*0.7, 720*0.4);
  mapSelImgs->push_back(mapone);
  mapSelImgs->push_back(maptwo);

  // Intro
  /// Initialisation
  sf::RectangleShape introRect;
  introRect.setSize(sf::Vector2f(1280, 720));
  introRect.setPosition(0, 0);

  sf::Event introEvents;
  sf::Clock introClock;
  bool introIsPlaying = true; // [SKIP] ici pour passer l'intro
  bool guiIsDisplayed = false;

  sf::Sprite * introOne = spriteFromTexture(&introOne_tex, false, 1);
  sf::Sprite * introTwo = spriteFromTexture(&introTwo_tex, false, 1);

  sf::Music music;
  if (!music.openFromFile("assets/ost.ogg"))
    return -1; // error
  music.play();

  while (introIsPlaying) {
    // get_close
    if (window->pollEvent(introEvents) && introEvents.type == sf::Event::Closed) {
      window->close();
      music.stop();
      introIsPlaying = false;
    }

    // lore_img1
    if (introClock.getElapsedTime() < sf::milliseconds(200)) {
      window->draw(*introOne);
      window->display();
    }

    // lore_img2
    if (introClock.getElapsedTime() > sf::milliseconds(8000)) {
      window->draw(*introTwo);
      window->display();
    }

    // fade_to_white
    if (introClock.getElapsedTime() > sf::milliseconds(16000)) {
      for (int i = 0; i < 256; i++){
        introRect.setFillColor(sf::Color(255, 255, 255, i));
        window->draw(introRect);
        window->display();
        sf::sleep(sf::milliseconds(12));
      }
      introIsPlaying = false;
    }
  }

  // Menu principal
  guiIsDisplayed = true;
  sf::Event menuEvents;
  window->clear();

  while (guiIsDisplayed) {
    // get_close
    if ((window->pollEvent(menuEvents) && menuEvents.type == sf::Event::Closed) || robs->getInGameStatus() == true) {
      music.stop();
      guiIsDisplayed = false;
    }

    robs->eventMgr(sf::Mouse::getPosition(*window), menuEvents);
    robs->update();
  }

  // Boucle de jeu
  while (robs->getInGameStatus() == true) {
    if (window->pollEvent(menuEvents) && menuEvents.type == sf::Event::Closed) {
      robs->setInGameStatus(false);
    }

    // Et ici on enjoy toute la logique de jeu lol
    // 1. si on est en début de jeu, placer les Robs
    // 2. gérer les tours
    // bref, voila, tout ça à faire dans Game soon

    robs->eventMgr(sf::Mouse::getPosition(*window), menuEvents);
    robs->update();
  }

  // Destructeurs (parce qu'on utilise pas encore de smart pointers)
  delete robs;
}
