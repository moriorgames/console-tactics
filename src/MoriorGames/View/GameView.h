#ifndef MORIOR_GAMES_VIEW_GAME_OBJECTS_VIEW_H
#define MORIOR_GAMES_VIEW_GAME_OBJECTS_VIEW_H

#include <vector>
#include "PixelView.h"

class GameView
{
public:
    GameView(sf::RenderWindow &window, short screenWidth, short screenHeight, short pixelRatio);
    void draw(short x, short y, sf::Color color);
    short getScreenHeight() const;
    short getScreenWidth() const;

private:
    sf::RenderWindow &window;
    short screenWidth = 0;
    short screenHeight = 0;
    short pixelRatio = 0;
    std::vector<std::vector<sf::RectangleShape>> rects;

    void init();
};

#endif
