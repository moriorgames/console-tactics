#include "Lamps.h"
#include <cmath>

#include <iostream>

float maxAngle = 2.6f;

Lamps::Lamps(GameView *gameView)
    : gameView{gameView}
{
    sampler = new TextureSampler("res/textures/lamp.jpg");
}

const std::vector<Coordinate> &Lamps::getLamps() const
{
    return lamps;
}

void Lamps::draw(sf::RenderWindow &window, float angle, float distance)
{
    float ceiling = (float) (gameView->getScreenHeight() / 2.0) - gameView->getScreenHeight() / distance;
    float floor = gameView->getScreenHeight() - ceiling;
    float height = floor - ceiling;
    float aspectRatio = sampler->getHeight() / sampler->getWidth();
    float width = height / aspectRatio;
    float midPoint = width / 2;
    float max = maxAngle * 2;
    float x = distance * sin(angle) + maxAngle;
    float r3 = x * gameView->getScreenWidth() / max;
    float finalX = r3 - midPoint;

    std::cout << " Angle " << angle << " finalX " << finalX << std::endl;

    for (float lx = 1; lx <= width; lx++) {
        for (float ly = 1; ly <= height; ly++) {
            float fSampleX = lx / width;
            float fSampleY = ly / height;
            auto color = sampler->getPixelColor(fSampleX, fSampleY, distance);

            gameView->draw(lx + finalX, ly + ceiling, color);
        }
    }
}
