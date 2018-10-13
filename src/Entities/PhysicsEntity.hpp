#pragma once

#include <SFML/Graphics.hpp>

class PhysicsEntity
{
    private:
        float m_Mass;
        sf::Vector2f m_Velocity;
        sf::Vector2f m_Acceleration;
    public:
        PhysicsEntity(float m_Mass);
        void Update(float deltaTime);
        void ApplyForce(const sf::Vector2f& force);
        void ApplyForce(float x, float y);
        void ApplyAcceleration(const sf::Vector2f& acceleration);
        void ApplyAcceleration(float x, float y);
        const sf::Vector2f& GetVelocity() const;
        void SetVelocity(const sf::Vector2f& velocity);
        void SetVelocity(float x, float y);
        float GetMass() const;
        void SetMass(float mass);
        // sfml has position
        virtual const sf::Vector2f& GetPosition() const = 0; 
        virtual void SetPosition(const sf::Vector2f& position) = 0;
        virtual void SetPosition(float x, float y) = 0;
};