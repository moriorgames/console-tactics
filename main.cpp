

#include <SFML/Graphics.hpp>
#include <cmath>

#include "src/MoriorGames/Entity/Player.h"

#define MAP_SIZE 40

using namespace std;

unsigned int pixelRatio = 4;

unsigned int screenWidth = 200;

unsigned int screenHeight = 120;

int mapSize = MAP_SIZE;

float fFOV = 3.14159f / 3.5f;    // Field of View
float fDepth = MAP_SIZE;            // Maximum rendering distance

wstring createMap();
void processInputEvents(sf::Clock &clock, wstring &map, Player *player, sf::RenderWindow &window);

int main()
{
    auto map = createMap();
    auto player = new Player;

    // Create main window
    sf::RenderWindow window(sf::VideoMode(screenWidth * pixelRatio, screenHeight * pixelRatio), "SFML Graphics");
    window.setFramerateLimit(60);
    sf::Clock clock;

    // Setup Colors
    sf::Color wallClose(150, 150, 150);
    sf::Color wallMedium(125, 125, 125);
    sf::Color wallFar(100, 100, 100);
    sf::Color wallFarFar(75, 75, 75);
    sf::Color darkestGray(25, 25, 25);

    sf::Color lightGreen(175, 255, 175);
    sf::Color green(120, 255, 120);
    sf::Color darkGreen(80, 240, 80);

    sf::Color lightBlue(100, 100, 255);
    sf::Color blue(70, 70, 255);
    sf::Color darkBlue(40, 40, 255);

    while (window.isOpen()) {

        processInputEvents(clock, map, player, window);

        window.clear(sf::Color::Blue);

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
            if (fDistanceToWall <= fDepth / 5.0f) {
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
                sf::Color floorShade;
                float b = 1.0f - (((float) y - screenHeight / 2.0f) / ((float) screenWidth / 2.0f));
                if (b < 0.6) {
                    skyShade = lightBlue;
                    floorShade = lightGreen;
                } else if (b < 0.75) {
                    skyShade = blue;
                    floorShade = green;
                } else {
                    skyShade = darkBlue;
                    floorShade = darkGreen;
                }

                sf::RectangleShape rectangle(sf::Vector2f(pixelRatio, pixelRatio));

                if (y <= nCeiling) {
                    rectangle.setFillColor(skyShade);
                } else if (y > nCeiling && y <= nFloor) {
                    rectangle.setFillColor(wallShade);
                } else {
                    rectangle.setFillColor(floorShade);
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
    map += L"#####################################..#";
    map += L"#.................####.................#";
    map += L"#..#############.....###...........#####";
    map += L"#..#.........####......########..####..#";
    map += L"#......##..............................#";
    map += L"#...#####....######..........###########";
    map += L"#.....#.......#######............#######";
    map += L"###............################.....####";
    map += L"##...#.#...............................#";
    map += L"#...##.####...#############....#....####";
    map += L"#..##..#...........##..####..###.......#";
    map += L"#..#...#......#######....##....######..#";
    map += L"#..................##.....#....#.......#";
    map += L"#......#####........###............#####";
    map += L"#..........########....................#";
    map += L"########################################";

    return map;
}

void processInputEvents(sf::Clock &clock, wstring &map, Player *player, sf::RenderWindow &window)
{
    auto elapsedTime = clock.getElapsedTime();
    clock.restart();

    sf::Event event;

    while (window.pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        player->setElapsedTime(elapsedTime.asSeconds());

        // Player rotation
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player->turnLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player->turnRight();
        }

        // Player moves
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player->moveForward();
            if (map.c_str()[(int) player->getX() * mapSize + (int) player->getY()] == '#') {
                player->moveBack();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player->moveBack();
            if (map.c_str()[(int) player->getX() * mapSize + (int) player->getY()] == '#') {
                player->moveForward();
            }
        }
    }
}
