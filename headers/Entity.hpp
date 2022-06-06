#ifndef ETY_HPP
#define ETY_HPP

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
  protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Texture * texture;
    sf::Sprite * sprite;

    sf::Shape * hitbox;

    bool alive;

  public:
    Entity();
    ~Entity();

    bool const isAlive() const { return alive; }

    virtual void move(Game * game) =0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
};

#endif
