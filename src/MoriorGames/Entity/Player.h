#ifndef MORIOR_GAMES_ENTITY_PLAYER_H
#define MORIOR_GAMES_ENTITY_PLAYER_H

#include <string>
#include <cmath>
#include "Map.h"
#include "../Observer/EventObservable.h"

class Player: public EventObservable
{
public:
    Player(Map *map);
    const float START_X = 3.0f;
    const float START_Y = 3.0f;
    const float START_ANGLE = .0f;
    const float SPEED_MOVE = 8.9f;
    const float SPEED_ROTATE = 4.1f;

    void update(EventState *) override;

    void turnLeft();
    void turnRight();
    void moveForward();
    void moveBack();

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    float getAngle() const;
    void setAngle(float angle);

    void setElapsedTime(float elapsedTime);

private:
    Map *map;
    float elapsedTime = .0f;
    float x = START_X, y = START_Y, angle = START_ANGLE;

};

#endif
