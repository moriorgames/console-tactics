#include "CeilingView.h"

CeilingView::CeilingView()
{
    auto ceilingTexture = new sf::Texture;
    ceilingTexture->loadFromFile("res/textures/ceiling-texture.jpg");
    ceilingTexture->setRepeated(true);

    ceiling.setSize(sf::Vector2f(1400, 200));
    ceiling.setPosition(0, 0);
    ceiling.setTexture(ceilingTexture);
    ceiling.setTextureRect(sf::IntRect(0, 0, 1400, 200));
    ceiling.setScale(sf::Vector2f(2.1f, 2.1f));
}

void CeilingView::update(EventState *eventState)
{
    if (eventState->isLeft()) {
        auto rect = ceiling.getTextureRect();
        rect.left -= MOVE;
        ceiling.setTextureRect(rect);
    }
    if (eventState->isRight()) {
        auto rect = ceiling.getTextureRect();
        rect.left += MOVE;
        ceiling.setTextureRect(rect);
    }
}

const sf::RectangleShape &CeilingView::getRect() const
{
    return ceiling;
}
