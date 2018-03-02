#ifndef MORIOR_GAMES_SERVICES_INPUT_EVENTS_H
#define MORIOR_GAMES_SERVICES_INPUT_EVENTS_H

#include <SFML/Graphics.hpp>
#include "../Entity/Map.h"
#include "../Entity/Player.h"

class InputEvents
{
public:
    InputEvents(sf::Clock &clock, Map *map, Player *player, sf::RectangleShape &rectangle, sf::RenderWindow &window);
    void process();

private:
    sf::Clock &clock;
    Map *map;
    Player *player;
    sf::RectangleShape &rectangle;
    sf::RenderWindow &window;
};

#endif
