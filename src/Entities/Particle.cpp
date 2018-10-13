#include "Particle.hpp" 
#include "PhysicsEntity.hpp"
#include <SFML/Graphics.hpp>

Particle::Particle(float mass, float radius) 
    : PhysicsEntity(mass)
{
    SetRadius(radius);
    m_Shape.setFillColor(sf::Color::White);
    m_Shape.setOutlineColor(sf::Color::Black);
    m_Shape.setOutlineThickness(2.0f);
}

const sf::Vector2f& Particle::GetPosition() const
{
    return m_Shape.getPosition();
}

void Particle::SetPosition(float x, float y)
{
    m_Shape.setPosition(x, y);
}

void Particle::SetPosition(const sf::Vector2f& position)
{
    m_Shape.setPosition(position);
}

float Particle::GetRadius() const
{
    return m_Shape.getRadius();
}

void Particle::SetRadius(float radius)
{
    m_Shape.setRadius(radius);
    m_Shape.setOrigin(radius, radius);
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Shape, states);
}
