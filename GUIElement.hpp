#ifndef GEL_HPP
#define GEL_HPP

#include <SFML/Graphics.hpp>

class GUIElement : public sf::Drawable {
  protected:
    sf::Vector2f position;

  public:
    const sf::Vector2f& getPosition() const {return position;}
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
};

#endif
