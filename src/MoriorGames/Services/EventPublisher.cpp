#include "EventPublisher.h"

InputEvents::InputEvents(sf::Clock &clock,
                         Map *map,
                         Player *player,
                         sf::RectangleShape &rectangle,
                         sf::RenderWindow &window)
    : clock{clock}, map{map}, player{player}, rectangle{rectangle}, window{window}
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
            auto rect = rectangle.getTextureRect();
            rect.left -= SKY_MOVE;
            rectangle.setTextureRect(rect);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player->turnRight();
            auto rect = rectangle.getTextureRect();
            rect.left += SKY_MOVE;
            rectangle.setTextureRect(rect);
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

void InputEvents::registerObserver(Subscribable *observer)
{
    observers.push_back(observer);
}

void InputEvents::removeObserver(Subscribable *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void InputEvents::notifyObservers()
{
    for (auto observer:observers) {
        observer->update();
    }
}
