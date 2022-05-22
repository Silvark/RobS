#include "Button.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "RobS");

  sf::Font myfont = sf::Font();
  if(!myfont.loadFromFile("RetroGaming.ttf"))
  {
     std::cout << "Erreur de chargement de la police d'écriture" << std::endl;
  }

  sf::CircleShape* circle = new sf::CircleShape();
  circle->setRadius(150);
  circle->setOutlineColor(sf::Color::Red);
  circle->setOutlineThickness(5);
  circle->setPosition(10, 20);

  sf::RectangleShape* rectangle = new sf::RectangleShape();
  rectangle->setSize(sf::Vector2f(100, 50));
  rectangle->setOutlineColor(sf::Color::Red);
  rectangle->setOutlineThickness(5);
  rectangle->setPosition(100, 200);

  std::vector<sf::Drawable*> my_shapes;
  my_shapes.push_back(circle);
  my_shapes.push_back(rectangle);
  ChangeMenu* play = new ChangeMenu(&window, my_shapes);

  Button mybutton = Button(sf::Vector2f(1280/2 - 230, 720*0.75), sf::Vector2f(460, 50), "Jouer!", myfont, play);

  while (window.isOpen()) {
    // check if button is hovered
    mybutton.hoveredStatus(sf::Mouse::getPosition(window));

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        delete play;
        for (auto i : my_shapes) {
          delete i;
        }
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          mybutton.onClick();
        }
        if (event.mouseButton.button == sf::Mouse::Right){

        }
      }
    }
    window.draw(mybutton);
    window.display();
  }
}
