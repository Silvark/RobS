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

    float mass;

    bool alive;
    bool isControlled;
    bool midAir;

  public:
    Entity();
    ~Entity();

    bool const isAlive() const { return alive; }
    void aliveStatus(bool value) { alive = value; }

    void updateVelocity();
    void updateVelocity(sf::Vector2f vel);
    void setPosition(sf::Vector2f& pos) { position = pos; }
    sf::Vector2f getPosition() const { return position; }

    void setMidair(bool value) { midAir = value; }
    bool const getMidair() { return midAir; }

    void setControlledStatus(bool value) { isControlled = value; }
    bool const getControlledStatus() { return isControlled; }

    virtual void move(Game * game) =0;
    virtual void onCollision(Game * game) =0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
};

#endif
