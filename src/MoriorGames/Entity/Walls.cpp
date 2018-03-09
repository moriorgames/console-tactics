#include "Walls.h"

Walls::Walls(GameView *gameView)
    : gameView{gameView}
{
    wallSampler = new TextureSampler("res/textures/wall-1.jpg");
}

int Walls::draw(sf::RenderWindow &window, int index, float distance, float sampleX)
{
    // Calculate distance to ceiling and floor
    auto height = gameView->getScreenHeight();
    int ceiling = (float) (height / 2.0) - height / ((float) distance);
    int floor = height - ceiling;

    for (int y = 0; y < height; y++) {
        if (y > ceiling && y <= floor) {
            drawRow(window, index, distance, sampleX, ceiling, floor, y);
        }
        index++;
    }

    return index;
}

void Walls::drawRow(sf::RenderWindow &window, int index, float distance, float sampleX, int ceiling, int floor, int y)
{
    float sampleY = ((float) y - (float) ceiling) / ((float) floor - (float) ceiling);
    gameView->draw(index, wallSampler->getPixelColor(sampleX, sampleY, distance));
}
