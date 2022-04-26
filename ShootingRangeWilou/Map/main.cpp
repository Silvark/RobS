#include "Map.hpp"
#include <SFML/Window.hpp>
#include <iostream>

int main() {
  sf::Color white = sf::Color(255, 255, 255, 255);
  Map game("test.png");

  sf::RenderWindow window(sf::VideoMode(game.getSize().x, game.getSize().y), "RobS");
	window.setActive(true);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::Q:
          window.close();
          break;
        default:
          break;
        }
      default:
        break;
      }
    }
    window.clear(white);
    window.draw(game);
    window.display();
  }
}
