
#include <SFML/Graphics.hpp>
#include <cmath>

#include <iostream>

#include "src/MoriorGames/Entity/Player.h"
#include "src/MoriorGames/Services/InputEvents.h"
#include "src/MoriorGames/Services/MapFactory.h"
#include "src/MoriorGames/Definitions.h"

using namespace std;

unsigned int pixelRatio = 6;

unsigned int screenWidth = 200;

unsigned int screenHeight = 120;

int mapSize = MAP_SIZE;

float fFOV = 3.14159f / 3.5f;

float fDepth = MAP_SIZE;

int main()
{
    sf::Clock clock;
    auto map = (new MapFactory)->createMap();
    auto player = new Player;
    // Create main window
    sf::RenderWindow window(sf::VideoMode(screenWidth * pixelRatio, screenHeight * pixelRatio), "SFML Graphics");

    auto inputEvents = new InputEvents(clock, map, player, window);

    // Setup Colors
    sf::Color wallClose(100, 100, 100);
    sf::Color wallMedium(80, 80, 80);
    sf::Color wallFar(65, 65, 65);
    sf::Color wallFarFar(40, 40, 40);
    sf::Color darkestGray(20, 20, 20);

    sf::Color lightFloor(100, 80, 50);
    sf::Color floor(90, 70, 40);
    sf::Color darkFloor(80, 60, 30);

    sf::Color lightSky(60, 70, 100);
    sf::Color sky(50, 60, 90);
    sf::Color darkSky(40, 50, 80);

    unsigned int index = 0;
    std::vector<sf::RectangleShape> rectangles(screenWidth * screenHeight);
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            sf::RectangleShape rectangle(sf::Vector2f(pixelRatio, pixelRatio));
            rectangle.setPosition(x * pixelRatio, y * pixelRatio);
            rectangles.at(index) = rectangle;
            index++;
        }
    }

    while (window.isOpen()) {

        inputEvents->process();
        window.clear(sf::Color::Blue);
        index = 0;

        for (int x = 0; x < screenWidth; x++) {
            // For each column, calculate the projected ray angle into world space
            float fRayAngle = (player->getAngle() - fFOV / 2.0f) + ((float) x / (float) screenWidth) * fFOV;

            // Find distance to wall
            float fStepSize = 0.1f;          // Increment size for ray casting, decrease to increase
            float fDistanceToWall = 0.0f; //                                      resolution

            bool bHitWall = false;        // Set when ray hits wall block

            float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
            float fEyeY = cosf(fRayAngle);

            // Incrementally cast ray from player, along ray angle, testing for
            // intersection with a block
            while (!bHitWall && fDistanceToWall < fDepth) {

                fDistanceToWall += fStepSize;
                int nTestX = (int) (player->getX() + fEyeX * fDistanceToWall);
                int nTestY = (int) (player->getY() + fEyeY * fDistanceToWall);

                // Test if ray is out of bounds
                if (nTestX < 0 || nTestX >= mapSize || nTestY < 0 || nTestY >= mapSize) {
                    bHitWall = true;            // Just set distance to maximum depth
                    fDistanceToWall = fDepth;
                } else {
                    // Ray is inbounds so test to see if the ray cell is a wall block
                    if (map.c_str()[nTestX * mapSize + nTestY] == '#') {
                        // Ray has hit wall
                        bHitWall = true;
                    }
                }
            }

            // Calculate distance to ceiling and floor
            int nCeiling = (float) (screenHeight / 2.0) - screenHeight / ((float) fDistanceToWall);
            int nFloor = screenHeight - nCeiling;

            // Shader walls based on distance
            sf::Color wallShade;
            if (fDistanceToWall <= fDepth / 6.0f) {
                wallShade = wallClose;
            } else if (fDistanceToWall < fDepth / 4.0f) {
                wallShade = wallMedium;
            } else if (fDistanceToWall < fDepth / 3.0f) {
                wallShade = wallFar;
            } else if (fDistanceToWall < fDepth / 2.0f) {
                wallShade = wallFarFar;
            } else {
                wallShade = darkestGray;
            }

            for (int y = 0; y < screenHeight; y++) {

                sf::Color skyShade;
                float skyFloat = 1.0f - (((float) y - screenHeight / 2.0f) / ((float) screenWidth / 2.0f));
                if (skyFloat < 1.3) {
                    skyShade = darkSky;
                } else if (skyFloat < 1.5) {
                    skyShade = sky;
                } else {
                    skyShade = lightSky;
                }

                sf::Color floorShade;
                float floorFloat = 1.0f - (((float) y - screenHeight / 2.0f) / ((float) screenWidth / 2.0f));
                if (floorFloat < 0.55) {
                    floorShade = lightFloor;
                } else if (floorFloat < 0.75) {
                    floorShade = floor;
                } else {
                    floorShade = darkFloor;
                }

                if (y <= nCeiling) {
                    rectangles.at(index).setFillColor(skyShade);
                } else if (y > nCeiling && y <= nFloor) {
                    rectangles.at(index).setFillColor(wallShade);
                } else {
                    rectangles.at(index).setFillColor(floorShade);
                }

                window.draw(rectangles.at(index));
                index++;
            }
        }

        window.display();
    }

    return EXIT_SUCCESS;
}
