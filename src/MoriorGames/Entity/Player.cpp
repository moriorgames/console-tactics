#include "Player.h"

Player::Player(Map *map)
    : map{map}
{
}

void Player::update(EventState *eventState)
{
    if (eventState->isLeft()) {
        turnLeft();
    }
    if (eventState->isRight()) {
        turnRight();
    }
    if (eventState->isUp()) {
        moveForward();
        if (map->isWallCollision(x, y)) {
            moveBack();
        }
    }
    if (eventState->isDown()) {
        moveBack();
        if (map->isWallCollision(x, y)) {
            moveForward();
        }
    }
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

float Player::getFieldOfView() const
{
    return fieldOfView;
}
