#include "headers/GUIElements.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2f sz,
               std::string txt, sf::Font& font, Command* act)
{
  // button element
  position = pos;
  element = sf::RectangleShape(sz);
  element.setPosition(pos);
  setColors(sf::Color(54, 145, 209, 255), sf::Color(13, 76, 120, 255));
  action = act;

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
       sf::Color btnCol, sf::Color outlineCol, Command* act)
{
  // button element
  Button(pos, sz, txt, font, act);

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
  action->execute();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(element, states);
  target.draw(desc, states);
}


Inventory::Inventory(sf::Vector2f pos, Player * o) {
  position = pos;
  owner = o;

  overlay_tex = new sf::Texture();
  overlay_tex->loadFromFile("assets/invoverlay.png");
  overlay = new sf::Sprite();
  overlay->setTexture(*overlay_tex);
  overlay->setPosition(position);
  
  frame = sf::RectangleShape(sf::Vector2f(60, 60));
  frame.setFillColor(sf::Color(0, 0, 0, 0));
  frame.setOutlineColor(sf::Color(255, 0, 0, 255));
  frame.setOutlineThickness(5);
}

Inventory::~Inventory() {
  delete overlay;
  delete overlay_tex;
}

void Inventory::onClick() {
  // implémenter chgt d'arme lors du clic?
}

void Inventory::hoveredStatus(const sf::Vector2i& mousePos) {
  if (mousePos.y >= position.y + 18 && mousePos.y <= position.y + 77) {
    // mesures prises à la main
    if (mousePos.x >= position.x + 18 && mousePos.x <= position.x + 77) {
      // bombe
      hovered = true;
      hoveredSlot = 1;
      frame.setPosition(sf::Vector2f(position.x + 18, position.y + 18));
      return;
    }

    if (mousePos.x >= position.x + 95 && mousePos.x <= position.x + 154) {
      // deagle
      hovered = true;
      hoveredSlot = 2;
      frame.setPosition(sf::Vector2f(position.x + 95, position.y + 18));
      return;
    }

    if (mousePos.x >= position.x + 172 && mousePos.x <= position.x + 231) {
      // mine
      hovered = true;
      hoveredSlot = 3;
      frame.setPosition(sf::Vector2f(position.x + 172, position.y + 18));
      return;
    }
  }
  hovered = false;
}

void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*overlay, states);
  if (hovered) {
    target.draw(frame, states);
  }
}
