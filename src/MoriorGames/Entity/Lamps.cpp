#include "Lamps.h"

Lamps::Lamps(short pixelRatio)
    : pixelRatio{pixelRatio}
{
    init();
}

const std::vector<Coordinate> &Lamps::getLamps() const
{
    return lamps;
}

int Lamps::draw(sf::RenderWindow &window, int index, float distance, float sampleX)
{
//    // Calculate distance to ceiling and floor
//    int ceiling = (float) (screenHeight / 2.0) - screenHeight / ((float) distance);
//    int floor = screenHeight - ceiling;
//
//    for (int y = 0; y < screenHeight; y++) {
//        if (y > ceiling && y <= floor) {
//            drawRow(window, index, distance, sampleX, ceiling, floor, y);
//        }
//        index++;
//    }

    return 0;
}

void Lamps::init()
{
    lampSampler = new TextureSampler("res/textures/lamp.jpg");
}

float Lamps::isLamp(short x, short y)
{
    auto it = std::find_if(lamps.begin(), lamps.end(), [x, y](Coordinate coordinate)
    {
        return coordinate.x == x && coordinate.y == y;
    });
    if (it != lamps.end()) {

        return 1;
    }

    return 0;
}

void Lamps::drawRow(sf::RenderWindow &window, int index, float distance, float sampleX, int ceiling, int floor, int y)
{
//    float sampleY = ((float) y - (float) ceiling) / ((float) floor - (float) ceiling);
//    rectangles.at(index).setFillColor(
//        wallSampler->getPixelColor(sampleX, sampleY, distance)
//    );
//    window.draw(rectangles.at(index));
}
