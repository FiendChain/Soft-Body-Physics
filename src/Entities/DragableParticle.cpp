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
        sf::Vector2f pos = (mousePosFloat - Particle::getPosition());
        sf::Vector2f velocity = pos / deltaTime;
        Particle::SetVelocity(velocity);
    }
}

bool DragableParticle::OnLClick(const sf::Vector2f& clickPos)
{
    sf::Vector2f posDiff = Particle::getPosition() - clickPos;
    float distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    if (distanceSquared < Particle::getRadius()*Particle::getRadius())
    {
        float radius = Particle::getRadius();
        sf::Vector2f size = sf::Vector2f(radius, radius) * 1.1f;
        m_OutlineBox.setSize(size*2.0f);
        m_OutlineBox.setOrigin(size);
        return true;
    }
    return false;
}

void DragableParticle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (DragableEntity::IsSelected())
        target.draw(m_OutlineBox, states); 
}