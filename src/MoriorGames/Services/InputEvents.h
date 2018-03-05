#ifndef MORIOR_GAMES_SERVICES_INPUT_EVENTS_H
#define MORIOR_GAMES_SERVICES_INPUT_EVENTS_H

#include <SFML/Graphics.hpp>
#include "../Entity/Map.h"
#include "../Entity/Player.h"
#include "../Observer/InputSubjectInterface.h"

class InputEvents: public InputSubjectInterface
{
public:
    const short SKY_MOVE = 4;

    InputEvents(sf::Clock &clock, Map *map, Player *player, sf::RectangleShape &rectangle, sf::RenderWindow &window);
    void registerObserver(InputObserverInterface *) override;
    void removeObserver(InputObserverInterface *) override;
    void notifyObservers() override;
    void process();

private:
    std::vector<InputObserverInterface *> observers;
    sf::Clock &clock;
    Map *map;
    Player *player;
    sf::RectangleShape &rectangle;
    sf::RenderWindow &window;
};

#endif
