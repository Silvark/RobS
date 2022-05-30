#include <unistd.h>
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "Button.hpp"

int main() {
  // Initialisation globale
  sf::RenderWindow window(sf::VideoMode(1280, 720), "RobS");

  sf::Font myFont;
  if (!myFont.loadFromFile("RetroGaming.ttf")) {
    std::cout << "Police d'écriture illisible."<< std::endl;
  }
  sf::Music music;
  if (!music.openFromFile("assets/ost.ogg"))
    return -1; // error

  // Intro
  /// Initialisation
  sf::Texture intro1;
  intro1.loadFromFile("assets/kartemer.png");
  sf::Sprite intro1Sprite;
  intro1Sprite.setTexture(intro1);

  sf::Texture intro2;
  intro2.loadFromFile("assets/battle.png");
  sf::Sprite intro2Sprite;
  intro2Sprite.setTexture(intro2);

  sf::RectangleShape introRect;
  introRect.setSize(sf::Vector2f(1280, 720));
  introRect.setPosition(0, 0);

  sf::Event introEvents;
  sf::Clock introClock;
  bool introIsPlaying = true;
  bool guiIsDisplayed = false;
  music.play();

  while (introIsPlaying) {
    // get_close
    if (window.pollEvent(introEvents) && introEvents.type == sf::Event::Closed) {
      window.close();
      music.stop();
      introIsPlaying = false;
    }

    // lore_img1
    if (introClock.getElapsedTime() < sf::milliseconds(200)) {
      window.draw(intro1Sprite);
      window.display();
    }

    // lore_img2
    if (introClock.getElapsedTime() > sf::milliseconds(8000)) {
      window.draw(intro2Sprite);
      window.display();
    }

    // fade_to_white
    if (introClock.getElapsedTime() > sf::milliseconds(16000)) {
      for (int i = 0; i < 256; i++){
        introRect.setFillColor(sf::Color(255, 255, 255, i));
        window.draw(introRect);
        window.display();
        sf::sleep(sf::milliseconds(12));
      }
      introIsPlaying = false;
    }
  }

  guiIsDisplayed = true;
  while (guiIsDisplayed) {
    // get_close
    if (window.pollEvent(introEvents) && introEvents.type == sf::Event::Closed) {
      window.close();
      music.stop();
      guiIsDisplayed = false;
    }

    introRect.setFillColor(sf::Color(255, 128, 128, 255));
    window.draw(introRect);
    window.display();
  }

  window.close();

  // Menu principal


  // Boucle de jeu
}
