#ifndef MORIOR_GAMES_VIEW_PIXEL_VIEW_H
#define MORIOR_GAMES_VIEW_PIXEL_VIEW_H

#include <SFML/Graphics.hpp>

class PixelView
{
public:
    PixelView(short x, short y, sf::RectangleShape &rect);
    short x;
    short y;
    sf::RectangleShape rect;
};

#endif
