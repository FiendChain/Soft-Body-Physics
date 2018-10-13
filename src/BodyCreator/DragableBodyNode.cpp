#include "DragableBodyNode.hpp"
#include <SFML/Graphics.hpp>
#include "Entities/DragablePoint.hpp"

#include <imgui/imgui.h>

DragableBodyNode::DragableBodyNode(float radius)
    : DragablePoint(radius),
      m_Mass(0)
{

}

bool DragableBodyNode::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);
            OnLClick(clickPos);
            return IsSelected();
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

void DragableBodyNode::OnImguiRender()
{
    float radius = DragablePoint::GetRadius();
    ImGui::Begin("Node editor");
    if (ImGui::SliderFloat("Radius", &radius, 5, 50))
    {
        SetRadius(radius);
    }
    ImGui::SliderFloat("Mass", &m_Mass, 0, 20);
    ImGui::End();

}

void DragableBodyNode::Update(sf::Window *window) 
{
    if (m_IsDragged && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        DragablePoint::Update(window);
    }
}

bool DragableBodyNode::OnLClick(const sf::Vector2f& clickPos)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        return IsSelected();
    }
    if (DragablePoint::OnLClick(clickPos))
    {
        SetSelected(true);
        m_IsDragged = true;
        return true;
    }
    SetSelected(false);
    m_IsDragged = false;
    return false;
}

void DragableBodyNode::OnLRelease()
{
    m_IsDragged = false;
}