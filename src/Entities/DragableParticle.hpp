#pragma once

#include "Particle.hpp"
#include "DragableEntity.hpp"
#include <SFML/Graphics.hpp>

class DragableParticle: public Particle, public DragableEntity
{
    private:
        sf::RectangleShape m_OutlineBox;
    public:
        DragableParticle(float mass, float radius);
        void Update(float deltaTime, sf::Window *window);
    private:
        virtual bool OnLClick(const sf::Vector2f& clickPos);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};