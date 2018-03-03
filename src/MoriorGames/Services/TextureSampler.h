#ifndef MORIOR_GAMES_SERVICES_TEXTURE_SAMPLER_H
#define MORIOR_GAMES_SERVICES_TEXTURE_SAMPLER_H

#include <SFML/Graphics.hpp>
#include <string>

class TextureSampler
{
public:
    explicit TextureSampler(const std::string &file);
    sf::Color getPixelColor(float x, float y, float distance);

private:
    sf::Image image;

    sf::Image initImage(const std::string &file);
    int darkByDistance(float distance);
};

#endif
