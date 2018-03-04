#include "Walls.h"

Walls::Walls(short screenWidth, short screenHeight, short pixelRatio)
    : screenWidth{screenWidth}, screenHeight{screenHeight}, pixelRatio{pixelRatio}
{
    initRectangles();
}

void Walls::draw(sf::RenderWindow &window,
                 TextureSampler *wallSampler,
                 unsigned int index,
                 float distance,
                 float sampleX,
                 int ceiling,
                 int floor,
                 int y)
{
    float sampleY = ((float) y - (float) ceiling) / ((float) floor - (float) ceiling);
    rectangles.at(index).setFillColor(
        wallSampler->getPixelColor(sampleX, sampleY, distance)
    );
    window.draw(rectangles.at(index));
}

void Walls::initRectangles()
{
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            sf::RectangleShape rectangle(sf::Vector2f(pixelRatio, pixelRatio));
            rectangle.setPosition(x * pixelRatio, y * pixelRatio);
            rectangles.push_back(rectangle);
        }
    }
}
