#ifndef CMD_HPP
#define CMD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Game;
class GUIElement;

class Command {
  protected:
    Game * game;
  public:
    virtual void execute() =0;
    virtual ~Command() {}
};

class ChangeMenu : public Command {
  private:
    std::vector<GUIElement *> * guielements;
    std::vector<sf::Sprite *> * elements;

  public:
    ChangeMenu(Game * istc, std::vector<GUIElement *> * gelts, std::vector<sf::Sprite *> * elts);

    void setTarget(Game * instance);
    void setPayload(std::vector<GUIElement *> * gelts, std::vector<sf::Sprite *> * elts);

    void execute();
};

class SetMap : public Command {
  private:
    std::string pathToMap;

  public:
    SetMap(Game * istc, std::string path);
    void execute();
};

class LaunchGame : public Command {
  private:
    sf::Sprite * background;

  public:
    LaunchGame(Game * istc, sf::Sprite * bg);
    void execute();
};

#endif
