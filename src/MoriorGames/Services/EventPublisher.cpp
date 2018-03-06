#include "EventPublisher.h"

EventPublisher::EventPublisher(sf::RenderWindow &window)
    : window{window}
{
    eventState = new EventState;
}

void EventPublisher::process()
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            eventState->setLeft(true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            eventState->setRight(true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            eventState->setUp(true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            eventState->setDown(true);
        }
    }
    notifyObservers();
    eventState->clear();
}

void EventPublisher::registerObserver(EventObservable *observer)
{
    observers.push_back(observer);
}

void EventPublisher::removeObserver(EventObservable *observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void EventPublisher::notifyObservers()
{
    for (auto observer:observers) {
        observer->update(eventState);
    }
}
