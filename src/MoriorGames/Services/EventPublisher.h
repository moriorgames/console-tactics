#ifndef MORIOR_GAMES_SERVICES_INPUT_EVENTS_H
#define MORIOR_GAMES_SERVICES_INPUT_EVENTS_H

#include <SFML/Graphics.hpp>
#include "../Entity/Map.h"
#include "../Entity/Player.h"
#include "../Observer/Publishable.h"

class InputEvents: public Publishable
{
public:
    const short SKY_MOVE = 4;

    InputEvents(sf::Clock &clock, Map *map, Player *player, sf::RectangleShape &rectangle, sf::RenderWindow &window);
    void registerObserver(Subscribable *) override;
    void removeObserver(Subscribable *) override;
    void notifyObservers() override;
    void process();

private:
    std::vector<Subscribable *> observers;
    sf::Clock &clock;
    Map *map;
    Player *player;
    sf::RectangleShape &rectangle;
    sf::RenderWindow &window;
};

#endif
