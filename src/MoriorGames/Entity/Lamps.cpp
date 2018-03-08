#include "Lamps.h"

Lamps::Lamps(short pixelRatio)
    : pixelRatio{pixelRatio}
{
    init();
}

int Lamps::draw(sf::RenderWindow &window, int index, float distance, float sampleX)
{
    return 0;
}

void Lamps::init()
{
    lampSampler = new TextureSampler("res/textures/lamp.jpg");
}

float Lamps::isLamp(short x, short y)
{
//    auto it = std::find_if(tiles.begin(), tiles.end(), [x, y](Tile *tile)
//    {
//        return tile->getX() == x && tile->getY() == y;
//    });
//    if (it != tiles.end()) {
//
//        return *it;
//    }

    return 0;
}