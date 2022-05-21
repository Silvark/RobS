#include "Button.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f sz,
               std::string txt, sf::Font& font)
{
  // button element
  position = pos;
  element = sf::RectangleShape(sz);
  element.setPosition(pos);
  element.setOutlineThickness(5);
  setColors(sf::Color(54, 145, 209, 255), sf::Color(13, 76, 120, 255));

  // text
  desc = sf::Text();
  desc.setString(txt);
  desc.setFont(font);
  sf::FloatRect textBounds = desc.getLocalBounds();
  desc.setOrigin(textBounds.width/2, textBounds.height/2);
  desc.setPosition(pos.x + sz.x/2, (pos.y + sz.y/2)-7);

  // hitbox
  setHitbox(pos, sz);
  hovered = false;
}

Button::Button(sf::Vector2f pos, sf::Vector2f sz, std::string txt,
       sf::Font& font, sf::Vector2f hbPos, sf::Vector2f hbSize,
       sf::Color btnCol, sf::Color outlineCol)
{
  // button element
  Button(pos, sz, txt, font);

  // custom hitbox & colors
  setHitbox(hbPos, hbSize);
  setColors(btnCol, outlineCol);
}

void Button::setColors(const sf::Color& btnCol, const sf::Color& outlineCol) {
  element.setFillColor(btnCol);
  element.setOutlineColor(outlineCol);
}
void Button::setHitbox(const sf::Vector2f& hbPos, const sf::Vector2f& hbSize) {
  hitboxPos = hbPos;
  hitboxSize = hbSize;
}

void Button::hoveredStatus(const sf::Vector2i& mousePos) {
  if (hitboxPos.x < mousePos.x && mousePos.x < hitboxPos.x + hitboxSize.x &&
      hitboxPos.y < mousePos.y && mousePos.y < hitboxPos.y + hitboxSize.y)
  {
    hovered = true;
    element.setOutlineThickness(5);
  }
  else {
    hovered = false;
    element.setOutlineThickness(0);
  }
}

void Button::onClick() {
  if (hovered)
    std::cout << "clicked!" << std::endl;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(element, states);
  target.draw(desc, states);
}
