#include "Lamps.h"

#include <iostream>
#include <cmath>

const double halfC = M_PI / 180;

float maxAngle = 1.23f;

Lamps::Lamps(GameView *gameView)
    : gameView{gameView}
{
    sampler = new TextureSampler("res/textures/lamp.jpg");
}

const std::vector<Coordinate> &Lamps::getLamps() const
{
    return lamps;
}

void Lamps::draw(sf::RenderWindow &window, float fFOV, float angle, float distance)
{
    float ceiling = (float) (gameView->getScreenHeight() / 2.0) - gameView->getScreenHeight() / distance;
    float floor = gameView->getScreenHeight() - ceiling;
    float height = floor - ceiling;
    float aspectRatio = sampler->getHeight() / sampler->getWidth();
    float width = height / aspectRatio;

    float max = maxAngle * 2;
    float x = distance * sin(angle) + maxAngle;
    float r3 = x * gameView->getScreenWidth() / max;

    for (float lx = 1; lx <= width; lx++) {
        for (float ly = 1; ly <= height; ly++) {
            float fSampleX = lx / width;
            float fSampleY = ly / height;
            auto color = sampler->getPixelColor(fSampleX, fSampleY, distance);

            gameView->draw(lx + r3, ly + ceiling, color);
        }
    }
}
