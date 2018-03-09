#include "GameView.h"

GameView::GameView(sf::RenderWindow &window, short screenWidth, short screenHeight, short pixelRatio)
    : window{window}, screenWidth{screenWidth}, screenHeight{screenHeight}, pixelRatio{pixelRatio}
{
    init();
}

void GameView::draw(int index, sf::Color color)
{
    rectangles.at(index).setFillColor(color);
    window.draw(rectangles.at(index));
}

short GameView::getScreenHeight() const
{
    return screenHeight;
}

void GameView::init()
{
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            sf::RectangleShape rectangle(sf::Vector2f(pixelRatio, pixelRatio));
            rectangle.setPosition(x * pixelRatio, y * pixelRatio);
            rectangles.push_back(rectangle);
        }
    }
}
