#pragma once

#include <SFML/Graphics.hpp>

class Particle: public sf::CircleShape
{
    private:
        float m_Mass;
        sf::Vector2f m_Velocity;
        sf::Vector2f m_Acceleration;
    public:
        Particle(float mass, float radius);
        void Update(float deltaTime);
        void ApplyForce(const sf::Vector2f& force);
        void ApplyForce(float x, float y);
        void ApplyAcceleration(const sf::Vector2f& acceleration);
        void ApplyAcceleration(float x, float y);
        void SetVelocity(const sf::Vector2f& velocity);
        void SetVelocity(float x, float y);
        inline const sf::Vector2f& GetVelocity() const { return m_Velocity; }
        inline const float GetMass() const { return m_Mass; }
};