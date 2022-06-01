#ifndef GAM_HPP
#define GAM_HPP

#include <SFML/Graphics.hpp>

#include "Map.hpp"
#include "GUIElement.hpp"

class Game {
  private:
    sf::RenderWindow * window;
    Map * terrain;
    sf::Sprite * bgimg;

    std::vector<GUIElement *> gui;
    // std::vector<Entity *> entities;
    std::vector<sf::Sprite *> elements;

    bool inGame;

  public:
    Game(sf::RenderWindow * wdw);
    ~Game();

    void update();
    bool eventMgr(const sf::Vector2i& mousePos, sf::Event& evt);

    void addGUIElement(GUIElement * guielt);
    void addGUIElement(std::vector<GUIElement *> guielts);
    void removeGUIElements();
    void cleanGUIElements();

    // void addEntity(Entity * ety);
    // void addEntity(std::vector<Entity *> etys);
    // void removeEntities();
    // void cleanEntities();

    void addElement(sf::Sprite * elt);
    void addElement(std::vector<sf::Sprite *> elts);
    void removeElements();

    void setBackground(sf::Sprite * sprite) { bgimg = sprite; }
    void setMap(std::string path);
    void setInGameStatus(bool value);

    bool const getInGameStatus() const { return inGame; }
};

#endif
