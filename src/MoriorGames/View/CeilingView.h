#ifndef MORIOR_GAMES_VIEW_CEILING_VIEW_H
#define MORIOR_GAMES_VIEW_CEILING_VIEW_H

#include <SFML/Graphics.hpp>
#include "../Observer/EventObservable.h"

class CeilingView: public EventObservable
{
public:
    const short MOVE = 4;

    CeilingView();
    void update(EventState *) override;
    const sf::RectangleShape &getRect() const;

private:
    sf::RectangleShape ceiling;
};


#endif
