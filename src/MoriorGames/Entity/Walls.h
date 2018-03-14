#ifndef MORIOR_GAMES_ENTITY_WALLS_H
#define MORIOR_GAMES_ENTITY_WALLS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Services/TextureSampler.h"
#include "../Entity/Player.h"
#include "../View/GameView.h"

class Walls
{
public:
    Walls(GameView *gameView);
    void draw(sf::RenderWindow &window, Player *player, Map *map);

private:
    GameView *gameView;
    TextureSampler *wallSampler;
    TextureSampler *lampSampler;

    void drawRow(sf::RenderWindow &window, int x, int y, float distance, float sampleX, int ceiling, int floor, short entity);
};

#endif
