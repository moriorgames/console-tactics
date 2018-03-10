#include "Lamps.h"

Lamps::Lamps(GameView *gameView)
    : gameView{gameView}
{
    sampler = new TextureSampler("res/textures/lamp.jpg");
}

const std::vector<Coordinate> &Lamps::getLamps() const
{
    return lamps;
}

void Lamps::draw(sf::RenderWindow &window, float fFOV, float fObjectAngle, float distance)
{
    float ceiling = (float) (gameView->getScreenHeight() / 2.0) - gameView->getScreenHeight() / distance;
    float floor = gameView->getScreenHeight() - ceiling;
    float height = floor - ceiling;
    float aspectRatio = sampler->getHeight() / sampler->getWidth();
    float width = height / aspectRatio;
    float middleOfObject = (0.8f * (fObjectAngle / (fFOV / 2.0f)) + 0.8f) * (float) gameView->getScreenHeight();

    for (float lx = 0; lx < width; lx++) {
        for (float ly = 0; ly < height; ly++) {
            float fSampleX = lx / width;
            float fSampleY = ly / height;
            int nObjectColumn = (int) (middleOfObject + lx - (width / 2.0f));
            int index = nObjectColumn * gameView->getScreenHeight() + ly + ceiling;
            auto color = sampler->getPixelColor(fSampleX, fSampleY, distance);

            if (index >= 0) {
                gameView->draw(index, color);
            }
        }
    }
}
