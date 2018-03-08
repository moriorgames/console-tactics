#ifndef MORIOR_GAMES_ENTITY_LAMPS_H
#define MORIOR_GAMES_ENTITY_LAMPS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Services/TextureSampler.h"

class Lamps
{
public:
    Lamps(short pixelRatio);
    int draw(sf::RenderWindow &window, int index, float distance, float sampleX);

    float isLamp(short x, short y);

private:
    short pixelRatio = 0;
    TextureSampler *lampSampler;

    void init();
};

#endif
