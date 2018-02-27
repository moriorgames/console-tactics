#ifndef MORIOR_GAMES_ENTITY_TILE_H
#define MORIOR_GAMES_ENTITY_TILE_H

#include <string>

class Tile
{
public:
    Tile();
    Tile(short x, short y, const std::string &type);
    short getX() const;
    short getY() const;
    const std::string &getType() const;

private:
    short x = 0, y = 0;
    std::string type = "";
};

#endif
