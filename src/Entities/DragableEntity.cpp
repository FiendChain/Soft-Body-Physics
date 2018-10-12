#include "DragableEntity.hpp"
#include <SFML/Graphics.hpp>

DragableEntity::DragableEntity()
    : m_Selected(false)
{

}

bool DragableEntity::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);
            m_Selected = OnLClick(clickPos);
            return m_Selected;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            OnLRelease();
        }
    }
    return false;
}

void DragableEntity::OnLRelease()
{
    m_Selected = false;
}