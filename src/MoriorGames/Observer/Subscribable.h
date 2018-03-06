#ifndef MORIOR_GAMES_OBSERVER_INPUT_SUBSCRIBER_INTERFACE_H
#define MORIOR_GAMES_OBSERVER_INPUT_SUBSCRIBER_INTERFACE_H

class Subscribable
{
public:
    virtual void update() = 0;
};

#endif
