#pragma once

#include "Particle.hpp"
#include "InteractableEntity.hpp"
#include <SFML/Graphics.hpp>

class Spring: public InteractableEntity
{
    private:
        sf::CircleShape m_Pivot;
        sf::RectangleShape m_OutlineBox;
        Particle m_Particle;
        float m_K;
        bool m_DragPivot, m_DragParticle;
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
        bool SelectItem(const sf::Vector2f& clickPos);
        void DragItem();
};