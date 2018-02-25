#ifndef MORIOR_GAMES_SERVICES_INPUT_EVENTS_H
#define MORIOR_GAMES_SERVICES_INPUT_EVENTS_H

#include <SFML/Graphics.hpp>
#include "../Entity/Player.h"

class InputEvents
{
public:
    InputEvents(sf::Clock &clock, std::wstring &map, Player *player, sf::RenderWindow &window);
    void process();

private:
    sf::Clock &clock;
    std::wstring &map;
    Player *player;
    sf::RenderWindow &window;
};

#endif
