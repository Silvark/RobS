#ifndef GAM_HPP
#define GAM_HPP

#include "Map.hpp"
#include "Player.hpp"
#include "Weapons.hpp"
#include "GUIElements.hpp"
#include "GameLogic.hpp"

class Game {
  private:
    sf::RenderWindow * window;
    Map * terrain;
    sf::Sprite * bgimg;

    std::vector<GUIElement *> gui;
    std::vector<Entity *> entities;
    std::vector<sf::Sprite *> elements;

    bool inGame;
    GameLogic * brain;

  public:
    Game(sf::RenderWindow * wdw, GameLogic * brn);
    ~Game();

    void update();

    void addGUIElement(GUIElement * guielt);
    void addGUIElement(std::vector<GUIElement *> guielts);
    void removeGUIElements();
    void cleanGUIElements();

    void addEntity(Entity * ety);
    void addEntity(std::vector<Entity *> etys);
    void removeEntities();
    void cleanEntities();

    void addElement(sf::Sprite * elt);
    void addElement(std::vector<sf::Sprite *> elts);
    void removeElements();

    void setBackground(sf::Sprite * sprite) { bgimg = sprite; }
    void setMap(std::string path);
    void setInGameStatus(bool value);

    bool const getInGameStatus() const { return inGame; }
};

#endif
