#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(short x, short y, const std::string &type)
    : x(x), y(y), type(type)
{
}

short Tile::getX() const
{
    return x;
}

short Tile::getY() const
{
    return y;
}

const std::string &Tile::getType() const
{
    return type;
}

