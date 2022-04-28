#include "Map.hpp"
#include <SFML/Window.hpp>
#include <iostream>

int main() {
  sf::Color white = sf::Color(255, 255, 255, 255);
  Map game("test.png");
  sf::View mapView, gameView;
  sf::Vector2i mouse;
  mapView.setSize(sf::Vector2f(150, 150));
  mapView.setViewport(sf::FloatRect(0.84375f, 0.722f, 0.15f, 0.15*1280/720));
  mapView.zoom(0.3f);
  sf::RenderWindow window(sf::VideoMode(game.getSize().x, game.getSize().y), "RobS");
	window.setActive(true);
  gameView = window.getDefaultView();

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
    window.setView(gameView);
    window.clear(white);
    window.draw(game);

    window.setView(mapView);
    mouse = sf::Mouse::getPosition(window);
    mapView.setCenter(mouse.x, mouse.y);
    window.draw(game);

    window.display();
  }
}
