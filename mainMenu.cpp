#include "Button.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "RobS");

  sf::Font myfont = sf::Font();
  if(!myfont.loadFromFile("RetroGaming.ttf"))
  {
     std::cout << "Erreur de chargement de la police d'écriture" << std::endl;
  }

  Button mybutton = Button(sf::Vector2f(1280/2 - 230, 720*0.75), sf::Vector2f(460, 50), "Jouer!", myfont);

  while (window.isOpen()) {
    // check if button is hovered
    mybutton.hoveredStatus(sf::Mouse::getPosition(window));

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          mybutton.onClick();
        }
        if (event.mouseButton.button == sf::Mouse::Right){

        }
      }
    }
    window.clear();
    window.draw(mybutton);
    window.display();
  }
}
