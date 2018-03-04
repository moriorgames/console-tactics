#ifndef MORIOR_GAMES_ENTITY_WALLS_H
#define MORIOR_GAMES_ENTITY_WALLS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Services/TextureSampler.h"

class Walls
{
public:
    Walls(short screenWidth, short screenHeight, short pixelRatio);
    void draw(sf::RenderWindow &window,
              TextureSampler *wallSampler,
              unsigned int index,
              float distance,
              float sampleX,
              int ceiling,
              int floor,
              int y);

private:
    short screenWidth = 0;
    short screenHeight = 0;
    short pixelRatio = 0;
    std::vector<sf::RectangleShape> rectangles;

    void initRectangles();
};

#endif
