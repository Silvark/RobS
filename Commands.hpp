#ifndef CMD_HPP
#define CMD_HPP

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
    std::vector<GUIElement *> elements;

  public:
    ChangeMenu() {}

    void setTarget(Game * instance);
    void setPayload(std::vector<GUIElement *> menu);

    void execute();
};

#endif
