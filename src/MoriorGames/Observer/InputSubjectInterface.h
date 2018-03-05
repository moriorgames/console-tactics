#ifndef MORIOR_GAMES_OBSERVER_INPUT_PUBLISHER_INTERFACE_H
#define MORIOR_GAMES_OBSERVER_INPUT_PUBLISHER_INTERFACE_H

#include "InputObserverInterface.h"

class InputSubjectInterface
{
public:
    virtual void registerObserver(InputObserverInterface *) = 0;
    virtual void removeObserver(InputObserverInterface *) = 0;
    virtual void notifyObservers() = 0;
};

#endif
