#ifndef MORIOR_GAMES_SERVICES_MAP_FACTORY_H
#define MORIOR_GAMES_SERVICES_MAP_FACTORY_H

#include <vector>
#include "../Entity/Map.h"
#include "../Definitions.h"

class MapFactory
{
public:
    Map *createMap();
};

#endif
