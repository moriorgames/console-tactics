#include "EventState.h"

bool EventState::isUp() const
{
    return up;
}

void EventState::setUp(bool up)
{
    this->up = up;
}

bool EventState::isDown() const
{
    return down;
}

void EventState::setDown(bool down)
{
    this->down = down;
}

bool EventState::isLeft() const
{
    return left;
}

void EventState::setLeft(bool left)
{
    this->left = left;
}

bool EventState::isRight() const
{
    return right;
}

void EventState::setRight(bool right)
{
    this->right = right;
}
