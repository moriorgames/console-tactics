#ifndef MORIOR_GAMES_OBSERVER_INPUT_SUBSCRIBER_INTERFACE_H
#define MORIOR_GAMES_OBSERVER_INPUT_SUBSCRIBER_INTERFACE_H

#include "../Entity/EventState.h"

class EventObservable
{
public:
    virtual void update(EventState *) = 0;
};

#endif
