#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>

class Command {
  public:
    virtual void execute() =0;
};

class ChangeMenu : public Command {
  private:
    sf::RenderWindow* surface;
    std::vector<sf::Drawable*> elements;
  public:
    ChangeMenu(sf::RenderWindow* window, std::vector<sf::Drawable*> menu) {
      elements = menu;
      surface = window;
    }

    void execute() {
      for (auto elt : elements) {
        (*surface).draw(*elt);
      }
    }
};

#endif
