#include "MapFactory.h"

Map * MapFactory::createMap()
{
    auto map = new Map;

    for (short x = 0; x < 5; ++x) {
        for (short y = 0; y < 5; ++y) {
            Tile *tile;
            if (x == 3 && y == 3) {
                tile = new Tile(x, y, TILE_WALL);
            } else {
                tile = new Tile(x, y, TILE_FLOOR);
            }
            map->addElement(tile);
        }
    }

    return map;
}
