#include "PhysicsEntity.hpp"
#include <SFML/Graphics.hpp>

PhysicsEntity::PhysicsEntity(float mass)
    : m_Mass(mass), 
      m_Velocity(0, 0), 
      m_Acceleration(0, 0)
{

}

void PhysicsEntity::Update(float deltaTime)
{
    #ifdef P_VERLET_PHYSICS
    sf::Vector2f oldPos = GetPosition();
    sf::Vector2f posDelta = m_Velocity*deltaTime + m_Acceleration*(0.5f*deltaTime*deltaTime);
    SetPosition(oldPos+posDelta);
    m_Velocity = posDelta / deltaTime;
    m_Acceleration.x = m_Acceleration.y = 0;
    #else
    m_Velocity += m_Acceleration * deltaTime;
    SetPosition(GetPosition() + m_Velocity * deltaTime);
    m_Acceleration.x = m_Acceleration.y = 0;
    #endif
}

void PhysicsEntity::ApplyForce(const sf::Vector2f& force)
{
    m_Acceleration += force / m_Mass; // f = m*a, a = f/m
}

void PhysicsEntity::ApplyForce(float x, float y)
{
    m_Acceleration.x += x / m_Mass;
    m_Acceleration.y += y / m_Mass;
}

void PhysicsEntity::ApplyAcceleration(const sf::Vector2f& acceleration)
{
    m_Acceleration += acceleration;
}

void PhysicsEntity::ApplyAcceleration(float x, float y)
{
    m_Acceleration.x += x;
    m_Acceleration.y += y;
}

const sf::Vector2f& PhysicsEntity::GetVelocity() const
{
    return m_Velocity;
}

void PhysicsEntity::SetVelocity(const sf::Vector2f& velocity)
{
    m_Velocity = velocity;
}

void PhysicsEntity::SetVelocity(float x, float y)
{
    m_Velocity.x = x;
    m_Velocity.y = y;
}

float PhysicsEntity::GetMass() const
{
    return m_Mass;
}

void PhysicsEntity::SetMass(float mass)
{
    m_Mass = mass;
}
