#ifndef CONSOLETACTICS_BACKGROUNDVIEW_H
#define CONSOLETACTICS_BACKGROUNDVIEW_H

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
