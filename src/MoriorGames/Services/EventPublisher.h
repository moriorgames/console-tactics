#ifndef MORIOR_GAMES_SERVICES_INPUT_EVENTS_H
#define MORIOR_GAMES_SERVICES_INPUT_EVENTS_H

#include <SFML/Graphics.hpp>
#include "../Entity/Map.h"
#include "../Entity/Player.h"
#include "../Observer/EventPublishable.h"

class EventPublisher: public EventPublishable
{
public:
    const short SKY_MOVE = 4;

    EventPublisher(sf::RectangleShape &rectangle, sf::RenderWindow &window);
    void registerObserver(EventObservable *) override;
    void removeObserver(EventObservable *) override;
    void notifyObservers() override;
    void process();

private:
    EventState *eventState;
    std::vector<EventObservable *> observers;
    sf::RectangleShape &rectangle;
    sf::RenderWindow &window;
};

#endif
