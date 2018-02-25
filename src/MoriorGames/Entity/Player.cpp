#include "Player.h"

void Player::turnLeft()
{
    angle -= SPEED_ROTATE * elapsedTime;
}

void Player::turnRight()
{
    angle += SPEED_ROTATE * elapsedTime;
}

void Player::moveForward()
{
    x += sinf(angle) * SPEED_MOVE * elapsedTime;
    y += cosf(angle) * SPEED_MOVE * elapsedTime;
}

void Player::moveBack()
{
    x -= sinf(angle) * SPEED_MOVE * elapsedTime;
    y -= cosf(angle) * SPEED_MOVE * elapsedTime;
}

float Player::getX() const
{
    return x;
}

void Player::setX(float x)
{
    this->x = x;
}

float Player::getY() const
{
    return y;
}

void Player::setY(float y)
{
    this->y = y;
}

float Player::getAngle() const
{
    return angle;
}

void Player::setAngle(float angle)
{
    this->angle = angle;
}

void Player::setElapsedTime(float elapsedTime)
{
    this->elapsedTime = elapsedTime;
}
