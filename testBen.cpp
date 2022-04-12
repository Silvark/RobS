#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

std::vector<sf::RectangleShape> tilesmaping(const std::vector<std::vector<int>> & level , std::array<sf::RectangleShape, 4> rects){

    std::vector<sf::RectangleShape> map;

    for (int i = 0;i<8;i++){
        for (int j = 0;j<16;j++){

            rects[level[i][j]].setPosition(sf::Vector2f(j*50, i*50));

            map.push_back(rects[level[i][j]]);
            std::cout << std::endl << level[i][j] << std::endl;
        }

    }

    return map;
}

void drawMap(const std::vector<sf::RectangleShape>& map, sf::RenderWindow& window){

    for(auto i : map)
        window.draw(i);
}

int main()
{
    std::cout << "e";
    std::vector<std::vector<int>> level =
    {
        {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3},
        {0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0},
        {0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0},
        {2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1}
    };

    sf::RenderWindow window(sf::VideoMode(16*50, 50*8), "First try");

    sf::RectangleShape shape(sf::Vector2f(20,20));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(100, 100);
    sf::RectangleShape rouge(sf::Vector2f(50, 50));
    rouge.setFillColor(sf::Color::Red);
    sf::RectangleShape vert(sf::Vector2f(50, 50));
    vert.setFillColor(sf::Color::Green);
    sf::RectangleShape bleu(sf::Vector2f(50, 50));
    bleu.setFillColor(sf::Color::Blue);
    sf::RectangleShape jaune(sf::Vector2f(50, 50));
    jaune.setFillColor(sf::Color::Yellow);

    std::array<sf::RectangleShape, 4> rects {rouge, vert, bleu, jaune};

    int posX = 50,posY = 50,avance = 10;

    std::vector<sf::RectangleShape> map = tilesmaping(level, rects);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Z)
                {
                    posY = posY - avance;
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    posY = posY + avance;
                }
                if (event.key.code == sf::Keyboard::Q)
                {
                    posX = posX - avance;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    posX = posX + avance;
                }
                if(posX>=11 && posX+21<(16*50) && posY>=1 && posY+21<=(8*50)){
                    shape.setPosition(posX, posY);
                }

        }

        window.clear();
        drawMap(map, window);
        window.draw(shape);
        window.display();
    }

    return 0;
}
