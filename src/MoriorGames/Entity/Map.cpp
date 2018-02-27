#include "Map.h"

const std::vector<Tile *> &Map::getTiles() const
{
    return tiles;
}

void Map::addElement(Tile *tile)
{
    tiles.push_back(tile);
}

Tile *Map::findTile(short x, short y)
{
    auto it = std::find_if(tiles.begin(), tiles.end(), [x, y](Tile *tile)
    {
        return tile->getX() == x && tile->getY() == y;
    });
    if (it != tiles.end()) {

        return *it;
    }

    return new Tile;
}

bool Map::isWallCollision(float fx, float fy)
{
    auto x = (short) fx;
    auto y = (short) fy;
    auto it = std::find_if(tiles.begin(), tiles.end(), [x, y](Tile *tile)
    {
        return tile->getX() == x && tile->getY() == y && tile->getType() == TILE_WALL;
    });

    return it != tiles.end();
}
