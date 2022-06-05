#include <unistd.h>
#include <SFML/Audio.hpp>

#include "Game.hpp"

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
  // [SKIP] ici pour passer l'intro
  bool introIsPlaying = false;

  // Initialisation globale
  /// Jeu
  std::cout << "[INFO] Création du jeu..." << std::endl;
  Game * robs = new Game();
  sf::RenderWindow * robsWindow = robs->getWindow();
  GameLogic * robsBrain = robs->getBrain();

  /// Police
  sf::Font myFont;
  if (!myFont.loadFromFile("assets/RetroGaming.ttf")) {
    std::cout << "[ERR] Police d'écriture illisible." << std::endl;
  }
  else { std::cout << "[INFO] Police d'écriture initialisée!" << std::endl; }

  /// Textures
  sf::Texture * bgimg_tex = new sf::Texture(); bgimg_tex->loadFromFile("assets/bg.png");
  sf::Texture * map01_tex = new sf::Texture(); map01_tex->loadFromFile("assets/map01.png");
  sf::Texture * map02_tex = new sf::Texture(); map02_tex->loadFromFile("assets/map02.png");
  sf::Texture * robslogo_tex = new sf::Texture(); robslogo_tex->loadFromFile("assets/robs.png");
  sf::Texture * introOne_tex = new sf::Texture(); introOne_tex->loadFromFile("assets/kartemer.png");
  sf::Texture * introTwo_tex = new sf::Texture(); introTwo_tex->loadFromFile("assets/battle.png");
  sf::Texture * gameBg_tex = new sf::Texture(); gameBg_tex->loadFromFile("assets/bg2.png");
  std::cout << "[INFO] Textures chargées! " << std::endl;

  // Main Menu
  /// Initialisation
  //// Background
  std::cout << "[INFO] Mise à jour du fond..." << std::endl;
  sf::Sprite * bgSprite = spriteFromTexture(bgimg_tex, false, 1);
  robs->setBackground(bgSprite);

  //// Logo
  std::cout << "[INFO] Ajout du logo..." << std::endl;
  sf::Sprite * robsLogo = spriteFromTexture(robslogo_tex, true, 1);
  robsLogo->setPosition(1280/2, 720*0.3);
  robs->addElement(robsLogo);


  //// Btn "Jouer"
  std::cout << "[INFO] Création de l'interface 1/3..." << std::endl;
  std::vector<sf::Sprite *> * mapSelImgs = new std::vector<sf::Sprite *>;
  std::vector<GUIElement *> * mapSelBtns = new std::vector<GUIElement *>;
  ChangeMenu * toMapSel = new ChangeMenu(robs, mapSelBtns, mapSelImgs);
  Button * btnToMapSel = new Button(sf::Vector2f(1280/2 - 230, 720*0.75), sf::Vector2f(460, 50), "Jouer!", myFont, toMapSel);
  robs->addGUIElement(btnToMapSel);


  // Map Selection
  /// Btns chgt map
  std::cout << "[INFO] Création de l'interface 2/3..."<< std::endl;
  SetMap * changeToMapone = new SetMap(robs, "assets/map01.png");
  SetMap * changeToMaptwo = new SetMap(robs, "assets/map02.png");
  sf::Sprite * gameBg = spriteFromTexture(gameBg_tex, false, 1);
  LaunchGame * toGame = new LaunchGame(robs, gameBg);
  Button * btnSelMapone = new Button(sf::Vector2f(1280*0.12, 720*0.6), sf::Vector2f(460, 50), "Minecraft Cave", myFont, changeToMapone);
  Button * btnSelMaptwo = new Button(sf::Vector2f(1280*0.52, 720*0.6), sf::Vector2f(460, 50), "King of the Hill", myFont, changeToMaptwo);
  Button * btnToGame = new Button(sf::Vector2f(1280/2 - 260, 720*0.75), sf::Vector2f(540, 50), "Jouer!", myFont, toGame);
  mapSelBtns->push_back(btnSelMapone);
  mapSelBtns->push_back(btnSelMaptwo);
  mapSelBtns->push_back(btnToGame);

  // Affichage maps
  std::cout << "[INFO] Création de l'interface 3/3..." << std::endl;
  sf::Sprite * mapone = spriteFromTexture(map01_tex, true, 0.36);
  sf::Sprite * maptwo = spriteFromTexture(map02_tex, true, 0.36);
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
  sf::Clock gameClock;

  sf::Sprite * introOne = spriteFromTexture(introOne_tex, false, 1);
  sf::Sprite * introTwo = spriteFromTexture(introTwo_tex, false, 1);

  std::cout << "[INFO] Démarrage de la musique..." << std::endl;
  sf::Music music;
  if (!music.openFromFile("assets/ost.ogg"))
    return -1; // error
  music.play();

  while (introIsPlaying) {
    // get_close
    if (robsWindow->pollEvent(introEvents) && introEvents.type == sf::Event::Closed) {
      robsWindow->close();
      music.stop();
      introIsPlaying = false;
    }

    // lore_img1
    if (gameClock.getElapsedTime() < sf::milliseconds(200)) {
      robsWindow->draw(*introOne);
      robsWindow->display();
    }

    // lore_img2
    if (gameClock.getElapsedTime() > sf::milliseconds(8000)) {
      robsWindow->draw(*introTwo);
      robsWindow->display();
    }

    // fade_to_white
    if (gameClock.getElapsedTime() > sf::milliseconds(16000)) {
      for (int i = 0; i < 256; i++){
        introRect.setFillColor(sf::Color(255, 255, 255, i));
        robsWindow->draw(introRect);
        robsWindow->display();
        sf::sleep(sf::milliseconds(12));
      }
      introIsPlaying = false;
    }
  }

  // Le jeu
  while (robsBrain->getFSM() != 99) {
    gameClock.restart();
    if (robsBrain->getFSM() != 0 && !introIsPlaying) {
      std::cout << "[INFO] Arrêt de la musique" << std::endl;
      music.stop();
      introIsPlaying = true; // recyclage du booléen
    }

    robsBrain->eventMgr(robs, sf::Mouse::getPosition(*(robsWindow)));
    robs->update();

    // majoration des fps
    sf::sleep(sf::seconds(1/60) - gameClock.getElapsedTime());
  }

  // Destructeurs (parce qu'on utilise pas encore de smart pointers)
  delete robs;
  delete bgimg_tex;
  delete map01_tex;
  delete map02_tex;
  delete robslogo_tex;
  delete introOne_tex;
  delete introTwo_tex;
  delete gameBg_tex;
}
