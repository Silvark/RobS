#ifndef MAPINH_HPP
#define MAPINH_HPP


#include <SFML/Graphics.hpp>
#include <vector>

class Map{

public:

    std::vector<sf::RectangleShape> carte;

    Map();
    std::vector<sf::RectangleShape> tilesmaping(const std::vector<std::vector<int>> & level , std::array<sf::RectangleShape, 4> rects);
    void drawMap(sf::RenderWindow& window);

};


#endif
