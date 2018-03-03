#ifndef MORIOR_GAMES_SERVICES_TEXTURE_SAMPLER_H
#define MORIOR_GAMES_SERVICES_TEXTURE_SAMPLER_H

#include <SFML/Graphics.hpp>

class TextureSampler
{
public:
    explicit TextureSampler(sf::Image &image);
    sf::Color getPixelColor(float x, float y, float distance);

private:
    sf::Image image;

    int darkByDistance(float distance);
};

#endif
