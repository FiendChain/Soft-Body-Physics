#pragma once
#include <SFML/Graphics.hpp>
#include "DragableEntity.hpp"

class DragablePoint: public sf::CircleShape, public DragableEntity
{
    private:
        sf::RectangleShape m_OutlineBox;
    public:
        DragablePoint(float radius);
        void Update(sf::Window *window);
    private:
        virtual bool OnLClick(const sf::Vector2f& clickPos);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};