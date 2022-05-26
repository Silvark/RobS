#ifndef GEL_HPP
#define GEL_HPP

#include <SFML/Graphics.hpp>
#include "Commands.hpp"

class GUIElement : public sf::Drawable {
  private:
    bool alive;
  protected:
    sf::Vector2f position;
    Command* action;
    bool hovered;

  public:
    const sf::Vector2f& getPosition() const {return position;}
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
    virtual void onClick() =0;
    virtual void hoveredStatus(const sf::Vector2i& mousePos) =0;

    bool const isAlive() const { return alive; }
    void aliveStatus(bool& value) { alive = value; }
};

#endif
