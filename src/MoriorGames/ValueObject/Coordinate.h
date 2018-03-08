#ifndef MORIOR_GAMES_VALUE_OBJECT_COORDINATE_H
#define MORIOR_GAMES_VALUE_OBJECT_COORDINATE_H

class Coordinate
{
public:
    int x, y;
    Coordinate(int x, int y);
    Coordinate(Coordinate *coordinate);
};

#endif
