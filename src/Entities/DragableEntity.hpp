#pragma once
#include <SFML/Graphics.hpp>

class DragableEntity
{
    private:
        bool m_Selected;
    public:
        DragableEntity();
        virtual bool OnEvent(const sf::Event& event);
        inline bool IsSelected() const { return m_Selected; }
    private:
        virtual bool OnLClick(const sf::Vector2f& clickPos) = 0;
        virtual void OnLRelease();
};