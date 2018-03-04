#include "Walls.h"

Walls::Walls(short screenWidth, short screenHeight, short pixelRatio)
    : screenWidth{screenWidth}, screenHeight{screenHeight}, pixelRatio{pixelRatio}
{
    init();
}

int Walls::draw(sf::RenderWindow &window, int index, float distance, float sampleX)
{
    // Calculate distance to ceiling and floor
    int ceiling = (float) (screenHeight / 2.0) - screenHeight / ((float) distance);
    int floor = screenHeight - ceiling;

    for (int y = 0; y < screenHeight; y++) {
        if (y > ceiling && y <= floor) {
            drawRow(window, index, distance, sampleX, ceiling, floor, y);
        }
        index++;
    }

    return index;
}

void Walls::init()
{
    wallSampler = new TextureSampler("res/textures/wall-1.jpg");
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            sf::RectangleShape rectangle(sf::Vector2f(pixelRatio, pixelRatio));
            rectangle.setPosition(x * pixelRatio, y * pixelRatio);
            rectangles.push_back(rectangle);
        }
    }
}

void Walls::drawRow(sf::RenderWindow &window, int index, float distance, float sampleX, int ceiling, int floor, int y)
{
    float sampleY = ((float) y - (float) ceiling) / ((float) floor - (float) ceiling);
    rectangles.at(index).setFillColor(
        wallSampler->getPixelColor(sampleX, sampleY, distance)
    );
    window.draw(rectangles.at(index));
}
