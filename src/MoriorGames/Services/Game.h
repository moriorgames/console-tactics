#ifndef MORIOR_GAMES_SERVICES_GAME_H
#define MORIOR_GAMES_SERVICES_GAME_H

#include <SFML/Graphics.hpp>
#include "../Definitions.h"
#include "TextureSampler.h"

class Game
{
public:
    Game();

private:
    unsigned int pixelRatio = 7;
    unsigned int screenWidth = 200;
    unsigned int screenHeight = 120;
    int mapSize = MAP_SIZE;
    float fFOV = 3.14159f / 3.5f;
    float fDepth = MAP_SIZE;

    void draw(sf::RenderWindow &window,
              TextureSampler *wallSampler,
              unsigned int index,
              std::vector<sf::RectangleShape> &rectangles,
              float fDistanceToWall,
              float fSampleX,
              int nCeiling,
              int nFloor,
              int y) const;
};

#endif
