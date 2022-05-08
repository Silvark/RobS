#ifndef ETY_H
#define ETY_H

#include <vector>
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
  private:
    // fonctionnel : informations sur l'entité
    sf::Vector2f spd;
    sf::Vector2f pos;
    int mass;
    int life;

    // fonctionnel : liste d'offsets par rapport à la position de l'entité
    // pour détecter quand il y a une collision sur une des surfaces de l'entité
    std::vector<sf::Vector2f> collide_points;

    // esthétique : faire tourner le sprite
    sf::Vector2f rot;
    sf::Vector2f center;
    float rot_increment;

    // esthétique : sprite
    sf::Image img;
    sf::Texture tex;

  public:
    virtual void detonate() =0; // en fin de vie, cette fonction doit s'exécuter
    virtual void move() =0; // deux fonctions move différentes car un joueur qui est aussi une entité, ne se déplacera pas comme une bombe
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
