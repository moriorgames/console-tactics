#ifndef MORIOR_GAMES_ENTITY_LAMPS_H
#define MORIOR_GAMES_ENTITY_LAMPS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Services/TextureSampler.h"
#include "../ValueObject/Coordinate.h"

class Lamps
{
public:
    Lamps(short pixelRatio);
    const std::vector<Coordinate> &getLamps() const;
    int draw(sf::RenderWindow &window, int index, float distance, float sampleX);
    float isLamp(short x, short y);

private:
    short pixelRatio = 0;
    TextureSampler *lampSampler;
    std::vector<Coordinate> lamps{
        {2, 3}, {5, 4}, {4, 6}, {9, 3}
    };

    void init();
    void drawRow(sf::RenderWindow &window, int index, float distance, float sampleX, int ceiling, int floor, int y);
};

#endif
