#include "MapFactory.h"

Map *MapFactory::createMap()
{
    auto map = new Map;

    for (short x = 0; x < structure.size(); ++x) {
        for (short y = 0; y < structure[x].size(); ++y) {
            Tile *tile;
            if (structure.at(x).at(y)) {
                tile = new Tile(x, y, TILE_WALL);
            } else {
                tile = new Tile(x, y, TILE_FLOOR);
            }
            map->addElement(tile);
        }
    }

    return map;
}
