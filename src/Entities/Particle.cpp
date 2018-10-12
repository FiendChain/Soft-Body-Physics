#include "Particle.hpp" 
#include <SFML/Graphics.hpp>

Particle::Particle(float mass, float radius) 
    : m_Mass(mass)
{
    setPosition(0, 0);
    setRadius(radius);
    setOrigin(radius, radius);
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setOutlineThickness(2.0f);
}

void Particle::Update(float deltaTime)
{
    m_Velocity += m_Acceleration * deltaTime;
    setPosition(getPosition() + m_Velocity * deltaTime);
    m_Acceleration.x = m_Acceleration.y = 0;
}

void Particle::ApplyForce(const sf::Vector2f& force)
{
    m_Acceleration += force / m_Mass; // f = m*a, a = f/m
}

void Particle::ApplyForce(float x, float y)
{
    m_Acceleration.x += x / m_Mass;
    m_Acceleration.y += y / m_Mass;
}

void Particle::ApplyAcceleration(const sf::Vector2f& acceleration)
{
    m_Acceleration += acceleration;
}

void Particle::ApplyAcceleration(float x, float y)
{
    m_Acceleration.x += x;
    m_Acceleration.y += y;
}

void Particle::SetVelocity(const sf::Vector2f& velocity)
{
    m_Velocity = velocity;
}

void Particle::SetVelocity(float x, float y)
{
    m_Velocity.x = x;
    m_Velocity.y = y;
}
