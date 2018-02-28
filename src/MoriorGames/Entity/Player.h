#ifndef MORIOR_GAMES_ENTITY_PLAYER_H
#define MORIOR_GAMES_ENTITY_PLAYER_H

#include <string>
#include <cmath>

class Player
{
public:
    const float START_X = 17.0f;
    const float START_Y = 6.0f;
    const float START_ANGLE = 4.7f;
    const float SPEED_MOVE = 7.7f;
    const float SPEED_ROTATE = 2.7f;

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
    float elapsedTime = .0f;
    float x = START_X, y = START_Y, angle = START_ANGLE;

};

#endif
