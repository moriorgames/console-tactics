#ifndef MORIOR_GAMES_OBSERVER_INPUT_PUBLISHER_INTERFACE_H
#define MORIOR_GAMES_OBSERVER_INPUT_PUBLISHER_INTERFACE_H

#include "Subscribable.h"

class Publishable
{
public:
    virtual void registerObserver(Subscribable *) = 0;
    virtual void removeObserver(Subscribable *) = 0;
    virtual void notifyObservers() = 0;
};

#endif
