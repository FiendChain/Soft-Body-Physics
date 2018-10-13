#include "StaticBody.hpp"

#include <memory>
#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>

StaticBody::StaticBody()
    : m_Joints(0), m_Connections(0), 
      m_CurrentParentNode(-1)
{

}

void StaticBody::Update(float deltaTime, sf::Window *window)
{
    for (auto& joint: m_Joints)
        joint->Update(window);
}

bool StaticBody::OnEvent(const sf::Event& event)
{
    for (auto& joint: m_Joints)
    {
        joint->OnEvent(event);
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f position(event.mouseButton.x, event.mouseButton.y);
            if (AddJoint(position) || RemoveJoint(position)) 
                return true;                
            else if (m_CurrentParentNode < 0 && StartConnection(position)) 
                return true;
            else if (m_CurrentParentNode >= 0 && CreateConnection(position))
                return true;
            else
                return false;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::LAlt:
            m_CurrentParentNode = -1;
            return true;
        }
    }
    return false;
}

void StaticBody::Reset()
{
    m_Connections.erase(m_Connections.begin(), m_Connections.end());
    m_Joints.erase(m_Joints.begin(), m_Joints.end());
    m_CurrentParentNode = -1;
}

