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
    sf::Sprite * bgimg;

    std::vector<GUIElement *> gui;
    std::vector<Entity *> entities;

  public:
    Game(sf::RenderWindow * wdw, Map * trn, sf::Sprite *);
    ~Game();

    void update();
    bool eventMgr(const sf::Vector2i& mousePos, sf::Event& evt);

    void addGUIElement(GUIElement * guielt);
    void addGUIElement(std::vector<GUIElement *> guielts);
    void removeGUIElements();
    void cleanGUIElements();

    void addEntity(Entity * ety);
    void addEntity(std::vector<Entity *> etys);
    void removeEntities();
    void cleanEntities();
};

#endif
