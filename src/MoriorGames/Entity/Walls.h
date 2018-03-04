#ifndef MORIOR_GAMES_ENTITY_WALLS_H
#define MORIOR_GAMES_ENTITY_WALLS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Services/TextureSampler.h"

class Walls
{
public:
    Walls(short screenWidth, short screenHeight, short pixelRatio);
    int draw(sf::RenderWindow &window, int index, float distance, float sampleX);

private:
    short screenWidth = 0;
    short screenHeight = 0;
    short pixelRatio = 0;
    TextureSampler *wallSampler;
    std::vector<sf::RectangleShape> rectangles;

    void init();
    void drawRow(sf::RenderWindow &window, int index, float distance, float sampleX, int ceiling, int floor, int y);
};

#endif
