#include "Game.h"

#include <cmath>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "../Entity/Player.h"
#include "../Entity/Map.h"
#include "../Entity/Walls.h"
#include "InputEvents.h"
#include "Logger.h"

using namespace std;

Game::Game()
{
    auto walls = new Walls(screenWidth, screenHeight, pixelRatio);
    auto logger = new Logger;
    sf::Clock clock;
    auto map = new Map;
    auto player = new Player;
    // Create main window
    sf::RenderWindow window(sf::VideoMode(screenWidth * pixelRatio, screenHeight * pixelRatio), "SFML Graphics");
    window.setFramerateLimit(60);

    sf::Color floorColor(90, 70, 40);

    auto skyTexture = new sf::Texture;
    skyTexture->loadFromFile("res/textures/sky-texture.jpg");
    skyTexture->setRepeated(true);
    sf::RectangleShape skyRectangle(sf::Vector2f(1400, 200));
    skyRectangle.setPosition(0, 0);
    skyRectangle.setTexture(skyTexture);
    skyRectangle.setTextureRect(sf::IntRect(0, 0, 1400, 200));
    skyRectangle.setScale(sf::Vector2f(2.1f, 2.1f));

    auto inputEvents = new InputEvents(clock, map, player, skyRectangle, window);

    while (window.isOpen()) {

        inputEvents->process();
        window.clear(floorColor);

        // Draw fixed background
        window.draw(skyRectangle);

        int index = 0;

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

            index = walls->draw(window, index, distanceToWall, fSampleX);
        }

        window.display();
        float fps = 1.0f / clock.getElapsedTime().asSeconds();
        auto stringFps = "FPS: " + to_string(fps);
        logger->log(stringFps);
    }
}
