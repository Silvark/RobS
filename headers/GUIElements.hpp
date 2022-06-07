#ifndef GEL_HPP
#define GEL_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Commands.hpp"
#include "Player.hpp"

class GUIElement : public sf::Drawable {
  private:
    bool alive;
    bool isActive;
  protected:
    sf::Vector2f position;
    Command* action;
    bool hovered;

  public:
    GUIElement() { alive = true; }
    const sf::Vector2f& getPosition() const { return position; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
    virtual void onClick() =0;
    virtual void hoveredStatus(const sf::Vector2i& mousePos) =0;

    bool const isHovered() const { return hovered; }
    bool const isAlive() const { return alive; }

    bool const getActiveStatus() { return isActive; }
    void setActiveStatus(bool value) { isActive = value; }

    void aliveStatus(bool value) { alive = value; }
};

class Button : public GUIElement {
  private:
    sf::RectangleShape element;
    sf::Text desc;

    // usuellement de la même taille que le bouton, sauf dans le menu de sélection de map
    sf::Vector2f hitboxPos;
    sf::Vector2f hitboxSize;
  public:
    Button(sf::Vector2f pos, sf::Vector2f sz,
           std::string txt, sf::Font& font, Command* act);                      // constructeur basique
    Button(sf::Vector2f pos, sf::Vector2f sz, std::string txt,
           sf::Font& font, sf::Vector2f hbPos, sf::Vector2f hbSize,
           sf::Color btnCol, sf::Color outlineCol, Command* act);               // constructeur avancé

    void setColors(const sf::Color& btnCol, const sf::Color& outlineCol);
    void setHitbox(const sf::Vector2f& hbPos, const sf::Vector2f& hbSize);

    void onClick();
    void hoveredStatus(const sf::Vector2i& mousePos);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class Inventory : public GUIElement {
  private:
    sf::Texture * overlay_tex;
    sf::Sprite * overlay;
    sf::RectangleShape frame;
    sf::RectangleShape selected;
    int hoveredSlot;
    int selectedSlot;

  public:
    Inventory(sf::Vector2f pos);
    ~Inventory();

    void updateSelected(int index);
    void setSelectedSlot(int index) { selectedSlot = index; }
    int const getSelectedSlot() { return selectedSlot; }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void onClick();
    void hoveredStatus(const sf::Vector2i& mousePos);
};

#endif
