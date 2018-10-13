#include "DragableBodyNode.hpp"
#include <SFML/Graphics.hpp>
#include "Entities/DragableEntity.hpp"

#include <imgui/imgui.h>

DragableBodyNode::DragableBodyNode(float radius)
    : m_Node(radius),
      m_Mass(0)
{
    // circle properties
    SetRadius(radius);
    m_Node.setFillColor(sf::Color::Red);
    m_Node.setOutlineColor(sf::Color::Black);
    m_Node.setOutlineThickness(2.0f);
    // box outline
    m_OutlineBox.setFillColor(sf::Color::Transparent);
    m_OutlineBox.setOutlineColor(sf::Color::Green);
    m_OutlineBox.setOutlineThickness(1.0f);
}

bool DragableBodyNode::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);
            OnLClick(clickPos);
            return m_IsSelected;
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
    float radius = m_Node.getRadius();
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
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);
        m_OutlineBox.setPosition(mousePosFloat);
        m_Node.setPosition(mousePosFloat);
    }
}

bool DragableBodyNode::CheckPositionInside(const sf::Vector2f& position) const
{
    sf::Vector2f posDiff = m_Node.getPosition() - position;
    float distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    float radius = m_Node.getRadius();
    if (distanceSquared < radius*radius)
        return true;
    return false;
}   

bool DragableBodyNode::OnLClick(const sf::Vector2f& clickPos)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        return m_IsSelected;
    }
    if (CheckPositionInside(clickPos))
    {
        RedrawOutline();
        m_IsDragged = m_IsSelected = true;
        return true;
    }
    m_IsDragged = m_IsSelected = false;
    return false;
}

void DragableBodyNode::OnLRelease()
{
    m_IsDragged = false;
}

void DragableBodyNode::RedrawOutline()
{
    float radius = m_Node.getRadius();
    sf::Vector2f size = sf::Vector2f(radius, radius) * 1.1f;
    m_OutlineBox.setSize(size*2.0f);
    m_OutlineBox.setOrigin(size);
}

void DragableBodyNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Node, states);
    if (m_IsSelected) 
        target.draw(m_OutlineBox, states);
    
}

void DragableBodyNode::SetRadius(float radius)
{
    m_Node.setRadius(radius);
    m_Node.setOrigin(sf::Vector2f(radius, radius));
    RedrawOutline();
}