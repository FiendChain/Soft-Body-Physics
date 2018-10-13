#include "DragablePoint.hpp"
#include <SFML/Graphics.hpp>
#include "DragableEntity.hpp"

DragablePoint::DragablePoint(float radius)
    : sf::CircleShape(radius)
{
    // circle properties
    setFillColor(sf::Color::Red);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(2.0f);
    // box outline
    m_OutlineBox.setFillColor(sf::Color::Transparent);
    m_OutlineBox.setOutlineColor(sf::Color::Green);
    m_OutlineBox.setOutlineThickness(1.0f);
}

void DragablePoint::Update(sf::Window *window) 
{
    if (DragableEntity::IsSelected())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);
        m_OutlineBox.setPosition(mousePosFloat);
        sf::CircleShape::setPosition(mousePosFloat);
    }
}

bool DragablePoint::OnLClick(const sf::Vector2f& clickPos)
{
    sf::Vector2f posDiff = getPosition() - clickPos;
    float distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    if (distanceSquared < getRadius()*getRadius())
    {
        float radius = getRadius();
        sf::Vector2f size = sf::Vector2f(radius, radius) * 1.1f;
        m_OutlineBox.setSize(size*2.0f);
        m_OutlineBox.setOrigin(size);
        return true;
    }
    return false;
}

void DragablePoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (DragableEntity::IsSelected())
        target.draw(m_OutlineBox, states);
}