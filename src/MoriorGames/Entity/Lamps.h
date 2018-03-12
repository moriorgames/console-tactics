#ifndef MORIOR_GAMES_ENTITY_LAMPS_H
#define MORIOR_GAMES_ENTITY_LAMPS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Services/TextureSampler.h"
#include "../ValueObject/Coordinate.h"
#include "../View/GameView.h"

class Lamps
{
public:
    Lamps(GameView *gameView);
    const std::vector<Coordinate> &getLamps() const;
    void draw(sf::RenderWindow &window, float angle, float distance);

private:
    GameView *gameView;
    TextureSampler *sampler;
    std::vector<Coordinate> lamps{
        {4, 7}
    };
};

#endif
