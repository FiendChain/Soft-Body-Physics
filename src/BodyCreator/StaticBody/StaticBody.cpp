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
    {
        joint->Update(window);
    }
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
            if (AddJoint(position)) {}
            else if (RemoveJoint(position)) {}    // remove a body if lctrl is held
            else if (m_CurrentParentNode < 0 && StartConnection(position)) {}   // start if lalt is held
            else if (m_CurrentParentNode >= 0 && CreateConnection(position)) {} // on click if current node exists
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::LAlt:
            m_CurrentParentNode = -1;
            break;
        }
    }
}

void StaticBody::Reset()
{
    m_Connections.erase(m_Connections.begin(), m_Connections.end());
    m_Joints.erase(m_Joints.begin(), m_Joints.end());
    m_CurrentParentNode = -1;
}

