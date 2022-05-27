#ifndef BTN_HPP
#define BTN_HPP

#include <iostream>
#include "GUIElement.hpp"

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

#endif
