#include "Map.h"

bool Map::isWallCollision(float fx, float fy)
{
    auto x = (short) fx;
    auto y = (short) fy;

    return structure.at(x).at(y) > FLOOR;
}

short Map::getCollisionEntity(float fx, float fy)
{
    auto x = (short) fx;
    auto y = (short) fy;

    return structure.at(x).at(y);
}
