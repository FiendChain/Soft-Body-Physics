#pragma once
#include <SFML/Graphics.hpp>

class DragableEntity
{
    private:
        bool m_Selected;
    public:
        DragableEntity();
        virtual bool OnEvent(const sf::Event& event);
        bool IsSelected() const { return m_Selected; }
        void SetSelected(bool selected) { m_Selected = selected; }
    private:
        virtual bool OnLClick(const sf::Vector2f& clickPos) = 0;
        virtual void OnLRelease();
};