#ifndef MORIOR_GAMES_ENTITY_WALLS_H
#define MORIOR_GAMES_ENTITY_WALLS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Services/TextureSampler.h"
#include "../View/GameView.h"

class Walls
{
public:
    Walls(GameView *gameView);
    void draw(sf::RenderWindow &window, int x, float distance, float sampleX);

private:
    GameView *gameView;
    TextureSampler *wallSampler;

    void drawRow(sf::RenderWindow &window, int x, int y, float distance, float sampleX, int ceiling, int floor);
};

#endif
