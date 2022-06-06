#ifndef ETY_HPP
#define ETY_HPP

#include <SFML/Graphics.hpp>
class Game;

const float GRAVITY = 9.81;

class Entity : public sf::Drawable {
  protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Texture * texture;
    sf::Sprite * sprite;

    sf::Shape * hitbox;
    float mass;

    bool alive;
    bool inMidair;

  public:
    Entity();
    ~Entity();

    bool const isAlive() const { return alive; }

    void updateVelocity();
    void setPosition(sf::Vector2f& pos) { position = pos; }
    sf::Vector2f getPosition() const { return position; }

    virtual void move(Game * game) =0;
    virtual void onCollision(Game * game) =0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
};

#endif
