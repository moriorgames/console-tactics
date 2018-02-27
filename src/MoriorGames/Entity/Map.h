#ifndef MORIOR_GAMES_ENTITY_MAP_H
#define MORIOR_GAMES_ENTITY_MAP_H

#include <vector>
#include "Tile.h"
#include "../Definitions.h"

class Map
{
public:
    const std::vector<Tile *> &getTiles() const;
    void addElement(Tile *);
    Tile *findTile(short x, short y);
    bool isWallCollision(float fx, float fy);

private:
    std::vector<Tile *> tiles;

};

#endif
