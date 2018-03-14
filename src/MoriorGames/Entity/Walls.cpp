#include "Walls.h"

Walls::Walls(GameView *gameView)
    : gameView{gameView}
{
    wallSampler = new TextureSampler("res/textures/wall-1.jpg");
    lampSampler = new TextureSampler("res/textures/lamp.jpg");
}

void Walls::draw(sf::RenderWindow &window, Player *player, Map *map)
{
    auto screenWidth = gameView->getScreenWidth();
    auto fieldOfView = player->getFieldOfView();

    for (int x = 0; x < screenWidth; x++) {
        // For each column, calculate the projected ray angle into world space
        float fRayAngle = (player->getAngle() - fieldOfView / 2.0f) + ((float) x / (float) screenWidth) * fieldOfView;

        // Find distance to wall
        float fStepSize = 0.1f;          // Increment size for ray casting, decrease to increase
        float distance = 0.0f; //                                      resolution

        bool hit = false;        // Set when ray hits wall block

        float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
        float fEyeY = cosf(fRayAngle);

        float sampleX = .0f;

        short entity = 1;
        // Incrementally cast ray from player, along ray angle, testing for
        // intersection with a block
        while (!hit && distance < MAP_SIZE) {

            distance += fStepSize;
            int nTestX = (int) (player->getX() + fEyeX * distance);
            int nTestY = (int) (player->getY() + fEyeY * distance);

            // Test if ray is out of bounds
            if (nTestX < 0 || nTestX >= MAP_SIZE || nTestY < 0 || nTestY >= MAP_SIZE) {
                hit = true;            // Just set distance to maximum depth
                distance = MAP_SIZE;
            } else {
                // Ray is inbounds so test to see if the ray cell is a wall block
                if (map->isWallCollision(nTestX, nTestY)) {
                    // Ray has hit wall
                    hit = true;
                    entity = map->getCollisionEntity(nTestX, nTestY);

                    // Determine where ray has hit wall. Break Block boundary
                    // int 4 line segments
                    float fBlockMidX = (float) nTestX + 0.5f;
                    float fBlockMidY = (float) nTestY + 0.5f;

                    float fTestPointX = player->getX() + fEyeX * distance;
                    float fTestPointY = player->getY() + fEyeY * distance;

                    float fTestAngle = atan2f((fTestPointY - fBlockMidY), (fTestPointX - fBlockMidX));

                    if (fTestAngle >= -3.14159f * 0.25f && fTestAngle < 3.14159f * 0.25f) {
                        sampleX = fTestPointY - (float) nTestY;
                    }
                    if (fTestAngle >= 3.14159f * 0.25f && fTestAngle < 3.14159f * 0.75f) {
                        sampleX = fTestPointX - (float) nTestX;
                    }
                    if (fTestAngle < -3.14159f * 0.25f && fTestAngle >= -3.14159f * 0.75f) {
                        sampleX = fTestPointX - (float) nTestX;
                    }
                    if (fTestAngle >= 3.14159f * 0.75f || fTestAngle < -3.14159f * 0.75f) {
                        sampleX = fTestPointY - (float) nTestY;
                    }
                }
            }
        }

        // Calculate distance to ceiling and floor
        auto height = gameView->getScreenHeight();
        int ceiling = (float) (height / 2.0) - height / ((float) distance);
        int floor = height - ceiling;

        for (int y = 0; y < height; y++) {
            if (y > ceiling && y <= floor) {
                drawRow(window, x, y, distance, sampleX, ceiling, floor, entity);
            }
        }
    }
}

void Walls::drawRow(sf::RenderWindow &window,
                    int x,
                    int y,
                    float distance,
                    float sampleX,
                    int ceiling,
                    int floor,
                    short entity)
{
    float sampleY = ((float) y - (float) ceiling) / ((float) floor - (float) ceiling);
    sf::Color color = wallSampler->getPixelColor(sampleX, sampleY, distance);
    if (entity == 2) {
        color = lampSampler->getPixelColor(sampleX, sampleY, distance);
    }

    gameView->draw(x, y, color);
}
