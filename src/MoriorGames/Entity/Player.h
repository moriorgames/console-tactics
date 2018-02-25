#ifndef MORIOR_GAMES_ENTITY_HERO_H
#define MORIOR_GAMES_ENTITY_HERO_H

#include <string>

class Player
{
public:
    const float START_X = 14.7f;
    const float START_Y = 5.09f;
    const float SPEED_MOVE = 7.0f;
    const float SPEED_ROTATE = 2.1f;

    void turnLeft();
    void turnRight();

    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    float getAngle() const;
    void setAngle(float angle);

    void setElapsedTime(float elapsedTime);

private:
    float elapsedTime = .0f;
    float x = START_X, y = START_Y, angle = .0f;

};

#endif
