

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <cmath>
using namespace std;

unsigned int pixelRatio = 8;

unsigned int screenWidth = 120;            // Console Screen Size X (columns)
unsigned int screenHeight = 40;            // Console Screen Size Y (rows)
int nMapWidth = 16;                // World Dimensions
int nMapHeight = 16;

float fPlayerX = 14.7f;            // Player Start Position
float fPlayerY = 5.09f;

float fPlayerA = 0.0f;            // Player Start Rotation
float fFOV = 3.14159f / 4.0f;    // Field of View
float fDepth = 16.0f;            // Maximum rendering distance
float fSpeed = 7.0f;            // Walking Speed
float rotateSpeed = 2.1f;

wstring createMap();
void processInputEvents(sf::Clock &clock, wstring &map, sf::RenderWindow &window);

int main()
{
    auto map = createMap();

    // Create main window
    sf::RenderWindow window(sf::VideoMode(screenWidth * pixelRatio, screenHeight * pixelRatio), "SFML Graphics");
    sf::Clock clock;


    // Setup Colors
    sf::Color lightGray(150, 150, 150);
    sf::Color gray(125, 125, 125);
    sf::Color darkGray(100, 100, 100);
    sf::Color darkestGray(50, 50, 50);
    sf::Color border(75, 75, 75);
    sf::Color lightGreen(150, 255, 150);
    sf::Color lightBlue(100, 100, 255);

    while (window.isOpen()) {

        processInputEvents(clock, map, window);

        window.clear(sf::Color::Blue);

        for (int x = 0; x < screenWidth; x++) {
            // For each column, calculate the projected ray angle into world space
            float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float) x / (float) screenWidth) * fFOV;

            // Find distance to wall
            float fStepSize = 0.1f;          // Increment size for ray casting, decrease to increase
            float fDistanceToWall = 0.0f; //                                      resolution

            bool bHitWall = false;        // Set when ray hits wall block
            bool bBoundary = false;        // Set when ray hits boundary between two wall blocks

            float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
            float fEyeY = cosf(fRayAngle);

            // Incrementally cast ray from player, along ray angle, testing for
            // intersection with a block
            while (!bHitWall && fDistanceToWall < fDepth) {

                fDistanceToWall += fStepSize;
                int nTestX = (int) (fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int) (fPlayerY + fEyeY * fDistanceToWall);

                // Test if ray is out of bounds
                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
                    bHitWall = true;            // Just set distance to maximum depth
                    fDistanceToWall = fDepth;
                } else {
                    // Ray is inbounds so test to see if the ray cell is a wall block
                    if (map.c_str()[nTestX * nMapWidth + nTestY] == '#') {
                        // Ray has hit wall
                        bHitWall = true;

                        // To highlight tile boundaries, cast a ray from each corner
                        // of the tile, to the player. The more coincident this ray
                        // is to the rendering ray, the closer we are to a tile
                        // boundary, which we'll shade to add detail to the walls
                        vector<pair<float, float>> p;

                        // Test each corner of hit tile, storing the distance from
                        // the player, and the calculated dot product of the two rays
                        for (int tx = 0; tx < 2; tx++)
                            for (int ty = 0; ty < 2; ty++) {
                                // Angle of corner to eye
                                float vy = (float) nTestY + ty - fPlayerY;
                                float vx = (float) nTestX + tx - fPlayerX;
                                float d = sqrt(vx * vx + vy * vy);
                                float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                                p.push_back(make_pair(d, dot));
                            }

                        // Sort Pairs from closest to farthest
                        sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right)
                        { return left.first < right.first; });

                        // First two/three are closest (we will never see all four)
                        float fBound = 0.01;
                        if (acos(p.at(0).second) < fBound) { bBoundary = true; }
                        if (acos(p.at(1).second) < fBound) { bBoundary = true; }
                        if (acos(p.at(2).second) < fBound) { bBoundary = true; }
                    }
                }
            }


            // Calculate distance to ceiling and floor
            int nCeiling = (float) (screenHeight / 2.0) - screenHeight / ((float) fDistanceToWall);
            int nFloor = screenHeight - nCeiling;

            // Shader walls based on distance
            sf::Color nShade;
            if (fDistanceToWall <= fDepth / 4.0f) {
                nShade = lightGray;    // Very close
            } else if (fDistanceToWall < fDepth / 3.0f) { nShade = gray; }
            else if (fDistanceToWall < fDepth / 2.0f) { nShade = darkGray; }
            else { nShade = darkestGray; }        // Too far away

            if (bBoundary) { nShade = border; } // Black it out

            for (int y = 0; y < screenHeight; y++) {
                sf::RectangleShape rectangle(sf::Vector2f(pixelRatio, pixelRatio));
                // Each Row
                if (y <= nCeiling) {
                    rectangle.setFillColor(lightBlue);
                } else if (y > nCeiling && y <= nFloor) {
                    rectangle.setFillColor(nShade);
                } else // Floor
                {
                    rectangle.setFillColor(lightGreen);
                }

                rectangle.setPosition(x * pixelRatio, y * pixelRatio);
                window.draw(rectangle);
            }

        }

        window.display();
    }

    return EXIT_SUCCESS;
}

wstring createMap()
{
    // Create Map of world space # = wall block, . = space
    wstring map;
    map += L"#########.......";
    map += L"#...............";
    map += L"#.......########";
    map += L"#..............#";
    map += L"#......##......#";
    map += L"#......##......#";
    map += L"#..............#";
    map += L"###............#";
    map += L"##.............#";
    map += L"#......####..###";
    map += L"#......#.......#";
    map += L"#......#.......#";
    map += L"#..............#";
    map += L"#......#########";
    map += L"#..............#";
    map += L"################";

    return map;
}

void processInputEvents(sf::Clock &clock, wstring &map, sf::RenderWindow &window)
{
    auto elapsedTime = clock.getElapsedTime();
    clock.restart();

    sf::Event event;

    while (window.pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // Player rotation
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            fPlayerA -= rotateSpeed * elapsedTime.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            fPlayerA += rotateSpeed * elapsedTime.asSeconds();
        }

        // Player moves
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            fPlayerX += sinf(fPlayerA) * fSpeed * elapsedTime.asSeconds();
            fPlayerY += cosf(fPlayerA) * fSpeed * elapsedTime.asSeconds();
            if (map.c_str()[(int) fPlayerX * nMapWidth + (int) fPlayerY] == '#') {
                fPlayerX -= sinf(fPlayerA) * fSpeed * elapsedTime.asSeconds();
                fPlayerY -= cosf(fPlayerA) * fSpeed * elapsedTime.asSeconds();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            fPlayerX -= sinf(fPlayerA) * fSpeed * elapsedTime.asSeconds();;
            fPlayerY -= cosf(fPlayerA) * fSpeed * elapsedTime.asSeconds();;
            if (map.c_str()[(int) fPlayerX * nMapWidth + (int) fPlayerY] == '#') {
                fPlayerX += sinf(fPlayerA) * fSpeed * elapsedTime.asSeconds();;
                fPlayerY += cosf(fPlayerA) * fSpeed * elapsedTime.asSeconds();;
            }
        }
    }
}
