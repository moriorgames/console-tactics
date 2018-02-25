#include "InputEvents.h"
#include "../Definitions.h"

InputEvents::InputEvents(sf::Clock &clock, std::wstring &map, Player *player, sf::RenderWindow &window)
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
            if (map.c_str()[(int) player->getX() * MAP_SIZE + (int) player->getY()] == '#') {
                player->moveBack();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player->moveBack();
            if (map.c_str()[(int) player->getX() * MAP_SIZE + (int) player->getY()] == '#') {
                player->moveForward();
            }
        }
    }
}
