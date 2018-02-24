

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <cmath>
using namespace std;

int nScreenWidth = 120;            // Console Screen Size X (columns)
int nScreenHeight = 40;            // Console Screen Size Y (rows)
int nMapWidth = 16;                // World Dimensions
int nMapHeight = 16;

float fPlayerX = 14.7f;            // Player Start Position
float fPlayerY = 5.09f;

float fPlayerA = 0.0f;            // Player Start Rotation
float fFOV = 3.14159f / 4.0f;    // Field of View
float fDepth = 16.0f;            // Maximum rendering distance
float fSpeed = 21.0f;            // Walking Speed
float fRotateSpeed = 11.0f;            // Walking Speed

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480, 32), "Hello SFML");

    sf::VertexArray triangle(sf::Triangles, 3);

// define the position of the triangle's points
    triangle[0].position = sf::Vector2f(10, 10);
    triangle[1].position = sf::Vector2f(100, 10);
    triangle[2].position = sf::Vector2f(100, 100);

// define the color of the triangle's points
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            window.clear(sf::Color::Blue);
            window.draw(triangle);
            window.display();
        }

    }

    return EXIT_SUCCESS;

//    initscr();
//    noecho();
//    cbreak();
//    curs_set(FALSE);
//
//    WINDOW *win = newwin(nScreenHeight, nScreenWidth, 0, 0);
//    keypad(win, TRUE);
//    nodelay(win, TRUE);
//
//    start_color();
//    init_pair(1, COLOR_WHITE, COLOR_BLACK);
//    init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
//    init_pair(3, COLOR_BLUE, COLOR_BLUE);
//    init_pair(4, COLOR_GREEN, COLOR_GREEN);
//    init_pair(5, COLOR_BLACK, COLOR_BLACK);
//
//
//    // Create Map of world space # = wall block, . = space
//    wstring map;
//    map += L"#########.......";
//    map += L"#...............";
//    map += L"#.......########";
//    map += L"#..............#";
//    map += L"#......##......#";
//    map += L"#......##......#";
//    map += L"#..............#";
//    map += L"###............#";
//    map += L"##.............#";
//    map += L"#......####..###";
//    map += L"#......#.......#";
//    map += L"#......#.......#";
//    map += L"#..............#";
//    map += L"#......#########";
//    map += L"#..............#";
//    map += L"################";
//
//    bool finished = false;
//    auto tp1 = chrono::system_clock::now();
//    auto tp2 = chrono::system_clock::now();
//
//    while (!finished) {
//        // We'll need time differential per frame to calculate modification
//        // to movement speeds, to ensure consistant movement, as ray-tracing
//        // is non-deterministic
//        tp2 = chrono::system_clock::now();
//        chrono::duration<float> elapsedTime = tp2 - tp1;
//        tp1 = tp2;
//        float fElapsedTime = elapsedTime.count();
//
//        // Player controls
//        auto keyInput = wgetch(win);
//
//        // Finish game
//        if (keyInput == 'q' || keyInput == 'Q') {
//            finished = true;
//        }
//
//        // Handle CCW Rotation
//        if (keyInput == 'a' || keyInput == 'A') {
//            fPlayerA -= fRotateSpeed * fElapsedTime;
//        }
//
//        // Handle CW Rotation
//        if (keyInput == 'd' || keyInput == 'D') {
//            fPlayerA += fRotateSpeed * fElapsedTime;
//        }
//
//        // Handle Forwards movement & collision
//        if (keyInput == 'w' || keyInput == 'W') {
//
//            fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
//            fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
//            if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
//            {
//                fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
//                fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
//            }
//        }
//
//        // Handle backwards movement & collision
//        if (keyInput == 's' || keyInput == 'S') {
//
//            fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
//            fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
//            if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
//            {
//                fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
//                fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
//            }
//        }
//
//        for (int x = 0; x < nScreenWidth; x++) {
//            // For each column, calculate the projected ray angle into world space
//            float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float) x / (float) nScreenWidth) * fFOV;
//
//            // Find distance to wall
//            float fStepSize = 0.1f;          // Increment size for ray casting, decrease to increase
//            float fDistanceToWall = 0.0f; //                                      resolution
//
//            bool bHitWall = false;        // Set when ray hits wall block
//            bool bBoundary = false;        // Set when ray hits boundary between two wall blocks
//
//            float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
//            float fEyeY = cosf(fRayAngle);
//
//            // Incrementally cast ray from player, along ray angle, testing for
//            // intersection with a block
//            while (!bHitWall && fDistanceToWall < fDepth) {
//
//                fDistanceToWall += fStepSize;
//                int nTestX = (int) (fPlayerX + fEyeX * fDistanceToWall);
//                int nTestY = (int) (fPlayerY + fEyeY * fDistanceToWall);
//
//                // Test if ray is out of bounds
//                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
//                    bHitWall = true;            // Just set distance to maximum depth
//                    fDistanceToWall = fDepth;
//                } else {
//                    // Ray is inbounds so test to see if the ray cell is a wall block
//                    if (map.c_str()[nTestX * nMapWidth + nTestY] == '#') {
//                        // Ray has hit wall
//                        bHitWall = true;
//
//                        // To highlight tile boundaries, cast a ray from each corner
//                        // of the tile, to the player. The more coincident this ray
//                        // is to the rendering ray, the closer we are to a tile
//                        // boundary, which we'll shade to add detail to the walls
//                        vector<pair<float, float>> p;
//
//                        // Test each corner of hit tile, storing the distance from
//                        // the player, and the calculated dot product of the two rays
//                        for (int tx = 0; tx < 2; tx++)
//                            for (int ty = 0; ty < 2; ty++) {
//                                // Angle of corner to eye
//                                float vy = (float) nTestY + ty - fPlayerY;
//                                float vx = (float) nTestX + tx - fPlayerX;
//                                float d = sqrt(vx * vx + vy * vy);
//                                float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
//                                p.push_back(make_pair(d, dot));
//                            }
//
//                        // Sort Pairs from closest to farthest
//                        sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right)
//                        { return left.first < right.first; });
//
//                        // First two/three are closest (we will never see all four)
//                        float fBound = 0.01;
//                        if (acos(p.at(0).second) < fBound) { bBoundary = true; }
//                        if (acos(p.at(1).second) < fBound) { bBoundary = true; }
//                        if (acos(p.at(2).second) < fBound) { bBoundary = true; }
//                    }
//                }
//            }
//
//
//            // Calculate distance to ceiling and floor
//            int nCeiling = (float) (nScreenHeight / 2.0) - nScreenHeight / ((float) fDistanceToWall);
//            int nFloor = nScreenHeight - nCeiling;
//
//            // Shader walls based on distance
//            char nShade = ' ';
//            if (fDistanceToWall <= fDepth / 4.0f) {
//                nShade = '#';    // Very close
//            } else if (fDistanceToWall < fDepth / 3.0f) { nShade = 'Y'; }
//            else if (fDistanceToWall < fDepth / 2.0f) { nShade = ':'; }
//            else { nShade = ' '; }        // Too far away
//
//            if (bBoundary) { nShade = ' '; } // Black it out
//
//
//            for (int y = 0; y < nScreenHeight; y++) {
//                // Each Row
//                if (y <= nCeiling) {
//                    mvwaddch(win, y, x, ' ' | COLOR_PAIR(3));
//                } else if (y > nCeiling && y <= nFloor) {
//                    mvwaddch(win, y, x, nShade | COLOR_PAIR(1));
//                } else // Floor
//                {
//                    mvwaddch(win, y, x, ' ' | COLOR_PAIR(4));
//                }
//            }
//
//        }
//
//        wrefresh(win);
//
//        // Display Stats
//        mvwprintw(win, 1, 1, "X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);
//
//    }
//
//    endwin();

    return 0;
}
