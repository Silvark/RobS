#ifndef ETY_HPP
#define ETY_HPP

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
  protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Texture * texture;
    sf::Sprite * sprite;

  public:
    Entity();
    ~Entity();

    virtual void move() =0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
};

#endif
