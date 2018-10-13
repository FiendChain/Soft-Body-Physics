#pragma once

#include "Entities/DragablePoint.hpp"
#include <SFML/Graphics.hpp>

class DragableBodyNode: public sf::Drawable
{
    public:
        bool m_OverrideOutline;
    private:
        sf::RectangleShape m_OutlineBox;
        sf::CircleShape m_Node;
        bool m_IsSelected, m_IsDragged;
        float m_Mass;
    public:
        DragableBodyNode(float radius);
        void Update(sf::Window *window);
        bool OnEvent(const sf::Event& event);
        void OnImguiRender();
        void SetRadius(float radius);
        inline void SetPosition(const sf::Vector2f& position) { m_Node.setPosition(position); }
        inline const sf::Vector2f& GetPosition() const { return m_Node.getPosition(); }
        inline float GetRadius() const { return m_Node.getRadius(); }
        inline float GetMass() const { return m_Mass; }
        inline bool IsSelected() const { return m_IsSelected; }
        inline bool IsDragged() const { return m_IsDragged; }
        bool CheckPositionInside(const sf::Vector2f& position) const;
    private:
        bool OnLClick(const sf::Vector2f& clickPos);
        void OnLRelease();
        void RedrawOutline();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};