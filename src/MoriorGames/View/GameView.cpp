#include "GameView.h"

GameView::GameView(sf::RenderWindow &window, short screenWidth, short screenHeight, short pixelRatio)
    : window{window}, screenWidth{screenWidth}, screenHeight{screenHeight}, pixelRatio{pixelRatio}
{
    init();
}

void GameView::draw(short x, short y, sf::Color color)
{
    if (x < rects.size() && y < rects.at(0).size()) {
        rects.at(x).at(y).setFillColor(color);
        window.draw(rects.at(x).at(y));
    }
}

short GameView::getScreenHeight() const
{
    return screenHeight;
}

short GameView::getScreenWidth() const
{
    return screenWidth;
}

void GameView::init()
{
    for (int x = 0; x < screenWidth; x++) {
        std::vector<sf::RectangleShape> vector;
        for (int y = 0; y < screenHeight; y++) {
            sf::RectangleShape rectangle(sf::Vector2f(pixelRatio, pixelRatio));
            rectangle.setPosition(x * pixelRatio, y * pixelRatio);
            vector.push_back(rectangle);
        }
        rects.push_back(vector);
    }
}
