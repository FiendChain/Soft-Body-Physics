#pragma once
#include <SFML/Graphics.hpp>
#include "DragableEntity.hpp"

class DragablePoint: public DragableEntity, public sf::Drawable
{
    private:
        sf::CircleShape m_Shape;
        sf::RectangleShape m_OutlineBox;
    public:
        DragablePoint(float radius);
        virtual void Update(sf::Window *window);
        float GetRadius() const;
        void SetRadius(float radius);
        const sf::Vector2f& GetPosition() const;
        void SetPosition(float x, float y);
        void SetPosition(const sf::Vector2f& position);
        bool CheckPositionInside(const sf::Vector2f& position) const;
        virtual bool OnLClick(const sf::Vector2f& clickPos);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};