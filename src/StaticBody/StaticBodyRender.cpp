#include "StaticBody.hpp"
#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>

void StaticBody::OnImGuiRender()
{
    ImGui::SliderFloat("Radius", &m_JointRadius, 0, 50);
    ImGui::SliderFloat("Mass", &m_JointMass, 0, 50);
    ImGui::SliderFloat("K", &m_K, 0, 50);
    ImGui::SliderFloat("C", &m_C, 0, 10);
    if (ImGui::Button("Reset"))
        Reset();
    for (auto& joint: m_Joints)
    {
        if (joint->IsSelected())
        {   
            joint->OnImguiRender();
            break;
        }
    }
}

void StaticBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // joints
    for (auto& joint: m_Joints)
    {
        if (joint) 
            target.draw(*joint, states);
    }
    // connections
    sf::VertexArray connections(sf::Lines);
    for (auto& connection: m_Connections)
    {
        auto& start = m_Joints.at(connection.start);
        auto& end = m_Joints.at(connection.end);
        connections.append(sf::Vertex(start->GetPosition(), sf::Color::Black));
        connections.append(sf::Vertex(end->GetPosition(), sf::Color::Black));
    }
    // render current connection being drawn
    if (m_CurrentParentNode >= 0)
    {
        auto& start = m_Joints.at(m_CurrentParentNode);
        connections.append(sf::Vertex(start->GetPosition(), sf::Color::Black));
        // mouse pos
    }
    target.draw(connections, states);
}