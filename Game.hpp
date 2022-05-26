#ifndef GAM_HPP
#define GAM_HPP

#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "Map.hpp"
#include "GUIElement.hpp"

class Game {
  private:
    sf::RenderWindow * window;
    Map * terrain;
    sf::Texture * bgimg;

    std::vector<GUIElement *> gui;
    std::vector<Entity *> entities;

  public:
    Game(sf::RenderWindow * wdw, Map * trn);
    ~Game();

    void update();

    void addEntity(Entity * ety);
    void addGUIElement(GUIElement * guielt);
    void addEntity(std::vector<Entity *> etys);
    void addGUIElement(std::vector<GUIElement *> guielts);
    void removeEntities();
    void removeGUIElements();
    void cleanEntities();
    void cleanGUIElements();
};

#endif
