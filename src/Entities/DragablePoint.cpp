#include "DragablePoint.hpp"
#include <SFML/Graphics.hpp>
#include "DragableEntity.hpp"

DragablePoint::DragablePoint(float radius)
    : m_Shape(radius)
{
    // circle properties
    m_Shape.setOrigin(radius, radius);
    m_Shape.setFillColor(sf::Color::Red);
    m_Shape.setOutlineColor(sf::Color::Black);
    m_Shape.setOutlineThickness(2.0f);
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
        m_Shape.setPosition(mousePosFloat);
    }
}

bool DragablePoint::OnLClick(const sf::Vector2f& clickPos)
{
    sf::Vector2f posDiff = m_Shape.getPosition() - clickPos;
    float distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    float radius = m_Shape.getRadius();
    if (distanceSquared < radius*radius)
    {
        sf::Vector2f size = sf::Vector2f(radius, radius) * 1.1f;
        m_OutlineBox.setSize(size*2.0f);
        m_OutlineBox.setOrigin(size);
        return true;
    }
    return false;
}

void DragablePoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Shape);
    if (DragableEntity::IsSelected())
        target.draw(m_OutlineBox, states);
}

float DragablePoint::GetRadius() const
{
    return m_Shape.getRadius();
}

void DragablePoint::SetRadius(float radius)
{
    m_Shape.setRadius(radius);
    m_Shape.setOrigin(radius, radius);
}

const sf::Vector2f& DragablePoint::GetPosition() const
{
    return m_Shape.getPosition();
}

void DragablePoint::SetPosition(float x, float y)
{
    m_Shape.setPosition(x, y);
}

void DragablePoint::SetPosition(const sf::Vector2f& position)
{
    m_Shape.setPosition(position);
}