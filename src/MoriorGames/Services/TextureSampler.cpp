#include "TextureSampler.h"
#include "../Definitions.h"

TextureSampler::TextureSampler(const std::string &file)
{
    init(file);
}

float TextureSampler::getHeight() const
{
    return height;
}

float TextureSampler::getWidth() const
{
    return width;
}

sf::Color TextureSampler::getPixelColor(float x, float y, float distance)
{
    float width = image.getSize().x;
    float height = image.getSize().y;
    sf::Color color(0, 0, 0);

    int sx = (int) (x * width);
    int sy = (int) (y * height - 1.0f);
    if (sx < 0 || sx >= width || sy < 0 || sy >= height) {
        return color;
    } else {

        auto darkness = darkByDistance(distance);

        color = image.getPixel(sx, sy);
        if (color.r < 20 && color.g > 230 && color.b < 20) {
            color.a = 0;
        }
        if (color.r > darkness) {
            color.r -= darkness;
        } else {
            color.r = 0;
        }
        if (color.g > darkness) {
            color.g -= darkness;
        } else {
            color.g = 0;
        }
        if (color.b > darkness) {
            color.b -= darkness;
        } else {
            color.b = 0;
        }

        return color;
    }
}

sf::Image TextureSampler::initImage(const std::string &file)
{
    sf::Texture texture;
    texture.loadFromFile(file);

    return texture.copyToImage();
}

int TextureSampler::darkByDistance(float distance)
{
    int darkness = 0;
    // Shader walls based on distance
    if (distance <= MAP_SIZE / 6.0f) {
        darkness = 0;
    } else if (distance < MAP_SIZE / 4.0f) {
        darkness = 25;
    } else if (distance < MAP_SIZE / 3.0f) {
        darkness = 50;
    } else if (distance < MAP_SIZE / 2.0f) {
        darkness = 75;
    } else {
        darkness = 100;
    }

    return darkness;
}

void TextureSampler::init(const std::string &file)
{
    image = initImage(file);
    height = image.getSize().y;
    width = image.getSize().x;
}
