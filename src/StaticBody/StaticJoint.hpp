#pragma once

#include "Entities/DragablePoint.hpp"
#include <SFML/Graphics.hpp>

class StaticJoint: public DragablePoint
{
    private:
        float m_Mass;
        bool m_IsDragged;
    public:
        StaticJoint(float radius, float mass);
        virtual void Update(sf::Window *window) override;
        bool OnEvent(const sf::Event& event);
        void OnImguiRender();
        inline float GetMass() const { return m_Mass; }
        inline bool IsDragged() const { return m_IsDragged; }
    private:
        virtual bool OnLClick(const sf::Vector2f& clickPos) override;
        virtual void OnLRelease() override;
};