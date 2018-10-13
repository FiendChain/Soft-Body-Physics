#include "DragableParticle.hpp"
#include "DragableEntity.hpp"
#include "Particle.hpp"

#include <SFML/Graphics.hpp>

DragableParticle::DragableParticle(float mass, float radius)
    : Particle(mass, radius),
      DragableEntity()
{
    m_OutlineBox.setFillColor(sf::Color::Transparent);
    m_OutlineBox.setOutlineColor(sf::Color::Green);
    m_OutlineBox.setOutlineThickness(1.0f);
}

void DragableParticle::Update(float deltaTime, sf::Window *window)
{
    Particle::Update(deltaTime);
    if (DragableEntity::IsSelected())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);
        m_OutlineBox.setPosition(mousePosFloat);
        // v = d/t
        sf::Vector2f pos = (mousePosFloat - GetPosition());
        sf::Vector2f velocity = pos / deltaTime;
        SetVelocity(velocity);
    }
}

bool DragableParticle::OnLClick(const sf::Vector2f& clickPos)
{
 
    if (CheckPositionInside(clickPos))
    {
        float radius = GetRadius();
        sf::Vector2f size = sf::Vector2f(radius, radius) * 1.1f;
        m_OutlineBox.setSize(size*2.0f);
        m_OutlineBox.setOrigin(size);
        return true;
    }
    return false;
}

bool DragableParticle::CheckPositionInside(const sf::Vector2f& position) const
{
    sf::Vector2f posDiff = GetPosition() - position;
    float distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    float radius = GetRadius();
    if (distanceSquared < radius*radius)
        return true;
    return false;
}

void DragableParticle::SetRadius(float radius)
{
    Particle::SetRadius(radius);
    m_OutlineBox.setSize(sf::Vector2f(2*radius, 2*radius));
    m_OutlineBox.setOrigin(radius, radius);
}

void DragableParticle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Particle::draw(target, states);
    if (DragableEntity::IsSelected())
        target.draw(m_OutlineBox, states); 
}