#ifndef MORIOR_GAMES_VIEW_GAME_OBJECTS_VIEW_H
#define MORIOR_GAMES_VIEW_GAME_OBJECTS_VIEW_H

#include <SFML/Graphics.hpp>
#include <vector>

class GameView
{
public:
    GameView(sf::RenderWindow &window, short screenWidth, short screenHeight, short pixelRatio);
    void draw(int index, sf::Color color);
    short getScreenHeight() const;
    short getScreenWidth() const;

private:
    sf::RenderWindow &window;
    short screenWidth = 0;
    short screenHeight = 0;
    short pixelRatio = 0;
    std::vector<sf::RectangleShape> rectangles;

    void init();
};

#endif
