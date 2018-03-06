#ifndef MORIOR_GAMES_OBSERVER_INPUT_PUBLISHER_INTERFACE_H
#define MORIOR_GAMES_OBSERVER_INPUT_PUBLISHER_INTERFACE_H

#include "EventObservable.h"

class EventPublishable
{
public:
    virtual void registerObserver(EventObservable *) = 0;
    virtual void removeObserver(EventObservable *) = 0;
    virtual void notifyObservers() = 0;
};

#endif
