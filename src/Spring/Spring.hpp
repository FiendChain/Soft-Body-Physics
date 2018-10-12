#pragma once

#include "Entities/DragableParticle.hpp"
#include "Entities/DragablePoint.hpp"
#include "Entities/InteractableEntity.hpp"
#include <SFML/Graphics.hpp>

class Spring: public InteractableEntity
{
    private:
        DragablePoint m_Pivot;
        DragableParticle m_Particle;
        float m_K;
    public:
        Spring(float k, float mass, const sf::Vector2f& pivot, const sf::Vector2f& point);
        void ApplyForce(const sf::Vector2f& force);
        void ApplyForce(float x, float y);
        void ApplyAcceleration(const sf::Vector2f& acceleration);
        void ApplyAcceleration(float x, float y);
        virtual void Update(float deltaTime, sf::Window *window) override;
        virtual bool OnEvent(const sf::Event& event) override;
        virtual void OnImGuiRender() override;
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};