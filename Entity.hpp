#ifndef ETY_HPP
#define ETY_HPP

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
  private:
    sf::Sprite * sprite;

  protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    int health;
    int energy;

  public:
    Entity();
    Entity(sf::Vector2f pos, sf::Vector2f vel, int h, int e, sf::Texture * tex);

    virtual void move() =0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;

    void setSprite(sf::Texture * tex);
};

#endif
