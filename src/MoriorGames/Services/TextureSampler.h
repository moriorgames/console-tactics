#ifndef MORIOR_GAMES_SERVICES_TEXTURE_SAMPLER_H
#define MORIOR_GAMES_SERVICES_TEXTURE_SAMPLER_H

#include <SFML/Graphics.hpp>
#include <string>

class TextureSampler
{
public:
    explicit TextureSampler(const std::string &file);
    float getHeight() const;
    float getWidth() const;
    sf::Color getPixelColor(float x, float y, float distance);

private:
    sf::Image image;
    float height;
    float width;

    sf::Image initImage(const std::string &file);
    int darkByDistance(float distance);
    void init(const std::string &file);
};

#endif
