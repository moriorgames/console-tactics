#include "Game.h"
#include "../Entity/Player.h"
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

        walls->draw(window, player, map);

        window.display();
        float fps = 1.0f / elapsedTime.asSeconds();
        auto stringFps = "FPS: " + to_string(fps);
        logger->log(stringFps);
    }
}
