#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicsEntity.hpp"

class Particle: public PhysicsEntity, public sf::Drawable
{
    private:
        sf::CircleShape m_Shape;
    public:
        Particle(float mass, float radius);
        virtual const sf::Vector2f& GetPosition() const override;
        virtual void SetPosition(float x, float y) override;
        virtual void SetPosition(const sf::Vector2f& position) override;
        float GetRadius() const;
        virtual void SetRadius(float radius);
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};