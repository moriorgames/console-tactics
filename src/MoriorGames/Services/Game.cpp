#include "Game.h"
#include "../Entity/Player.h"
#include "../Entity/Lamps.h"
#include "../Entity/Walls.h"
#include "EventPublisher.h"
#include "Logger.h"
#include "../View/CeilingView.h"
#include "../View/GameView.h"

using namespace std;

Game::Game()
{
    auto logger = new Logger;
    sf::Clock clock;
    auto map = new Map;
    auto player = new Player(map);
    // Create main window
    sf::RenderWindow window(sf::VideoMode(screenWidth * pixelRatio, screenHeight * pixelRatio), "SFML Graphics");
    window.setFramerateLimit(60);

    sf::Color floorColor(90, 70, 40);

    auto ceilingView = new CeilingView;
    auto gameView = new GameView(window, screenWidth, screenHeight, pixelRatio);
    auto walls = new Walls(gameView);
    auto lamps = new Lamps(gameView);

    auto eventPublisher = new EventPublisher(window);
    eventPublisher->registerObserver(player);
    eventPublisher->registerObserver(ceilingView);

    while (window.isOpen()) {

        auto elapsedTime = clock.getElapsedTime();
        clock.restart();
        player->setElapsedTime(elapsedTime.asSeconds());
        eventPublisher->process();
        window.clear(floorColor);

        // Draw fixed background
        window.draw(ceilingView->getRect());

        for (int x = 0; x < screenWidth; x++) {
            // For each column, calculate the projected ray angle into world space
            float fRayAngle = (player->getAngle() - fFOV / 2.0f) + ((float) x / (float) screenWidth) * fFOV;

            // Find distance to wall
            float fStepSize = 0.1f;          // Increment size for ray casting, decrease to increase
            float distanceToWall = 0.0f; //                                      resolution

            bool bHitWall = false;        // Set when ray hits wall block

            float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
            float fEyeY = cosf(fRayAngle);

            float fSampleX = .0f;

            // Incrementally cast ray from player, along ray angle, testing for
            // intersection with a block
            while (!bHitWall && distanceToWall < fDepth) {

                distanceToWall += fStepSize;
                int nTestX = (int) (player->getX() + fEyeX * distanceToWall);
                int nTestY = (int) (player->getY() + fEyeY * distanceToWall);

                // Test if ray is out of bounds
                if (nTestX < 0 || nTestX >= mapSize || nTestY < 0 || nTestY >= mapSize) {
                    bHitWall = true;            // Just set distance to maximum depth
                    distanceToWall = fDepth;
                } else {
                    // Ray is inbounds so test to see if the ray cell is a wall block
                    if (map->isWallCollision(nTestX, nTestY)) {
                        // Ray has hit wall
                        bHitWall = true;

                        // Determine where ray has hit wall. Break Block boundary
                        // int 4 line segments
                        float fBlockMidX = (float) nTestX + 0.5f;
                        float fBlockMidY = (float) nTestY + 0.5f;

                        float fTestPointX = player->getX() + fEyeX * distanceToWall;
                        float fTestPointY = player->getY() + fEyeY * distanceToWall;

                        float fTestAngle = atan2f((fTestPointY - fBlockMidY), (fTestPointX - fBlockMidX));

                        if (fTestAngle >= -3.14159f * 0.25f && fTestAngle < 3.14159f * 0.25f) {
                            fSampleX = fTestPointY - (float) nTestY;
                        }
                        if (fTestAngle >= 3.14159f * 0.25f && fTestAngle < 3.14159f * 0.75f) {
                            fSampleX = fTestPointX - (float) nTestX;
                        }
                        if (fTestAngle < -3.14159f * 0.25f && fTestAngle >= -3.14159f * 0.75f) {
                            fSampleX = fTestPointX - (float) nTestX;
                        }
                        if (fTestAngle >= 3.14159f * 0.75f || fTestAngle < -3.14159f * 0.75f) {
                            fSampleX = fTestPointY - (float) nTestY;
                        }
                    }
                }
            }

            walls->draw(window, x, distanceToWall, fSampleX);
        }

        for (auto &coordinate : lamps->getLamps()) {

            // Can object be seen?
            float fVecX = coordinate.x - player->getX();
            float fVecY = coordinate.y - player->getY();
            float fDistanceFromPlayer = sqrtf(fVecX * fVecX + fVecY * fVecY);

            float fEyeX = sinf(player->getAngle());
            float fEyeY = cosf(player->getAngle());

            // Calculate angle between lamp and players feet, and players looking direction
            // to determine if the lamp is in the players field of view
            float fObjectAngle = atan2f(fEyeY, fEyeX) - atan2f(fVecY, fVecX);
            if (fObjectAngle < -3.14159f) {
                fObjectAngle += 2.0f * 3.14159f;
            }
            if (fObjectAngle > 3.14159f) {
                fObjectAngle -= 2.0f * 3.14159f;
            }

            bool bInPlayerFOV = fabs(fObjectAngle) < fFOV / 2.0f;

            if (bInPlayerFOV && fDistanceFromPlayer >= 0.5f) {

                lamps->draw(window, fFOV, fObjectAngle, fDistanceFromPlayer);

            }
        }

        window.display();
        float fps = 1.0f / elapsedTime.asSeconds();
        auto stringFps = "FPS: " + to_string(fps);
        logger->log(stringFps);
    }
}
