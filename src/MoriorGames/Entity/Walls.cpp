#include "Walls.h"

Walls::Walls(GameView *gameView)
    : gameView{gameView}
{
    wallSampler = new TextureSampler("res/textures/wall-1.jpg");
}

void Walls::draw(sf::RenderWindow &window, int x, float distance, float sampleX)
{
    // Calculate distance to ceiling and floor
    auto height = gameView->getScreenHeight();
    int ceiling = (float) (height / 2.0) - height / ((float) distance);
    int floor = height - ceiling;

    for (int y = 0; y < height; y++) {
        if (y > ceiling && y <= floor) {
            drawRow(window, x, y, distance, sampleX, ceiling, floor);
        }
    }
}

void Walls::drawRow(sf::RenderWindow &window, int x, int y, float distance, float sampleX, int ceiling, int floor)
{
    float sampleY = ((float) y - (float) ceiling) / ((float) floor - (float) ceiling);
    gameView->draw(x, y, wallSampler->getPixelColor(sampleX, sampleY, distance));
}
