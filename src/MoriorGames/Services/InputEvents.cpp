#include "InputEvents.h"
#include "../Definitions.h"

InputEvents::InputEvents(sf::Clock &clock, Map *map, Player *player, sf::RenderWindow &window)
    : clock{clock}, map{map}, player{player}, window{window}
{
}

void InputEvents::process()
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
            if (map->isWallCollision(player->getX(), player->getY())) {
                player->moveBack();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player->moveBack();
            if (map->isWallCollision(player->getX(), player->getY())) {
                player->moveForward();
            }
        }
    }
}
