#include "BodyCreator.hpp"
#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>
#include <imgui-sfml/imgui-SFML-addons.h>


static sf::Vector2f GetMousePosFloat(sf::Window& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return sf::Vector2f(mousePos.x, mousePos.y);
}

void BodyCreator::Render()
{
    m_Window.clear(sf::Color::White);
    for (auto& node: m_Nodes)
    {
        if (node) m_Window.draw(*node);
    }
    // render connections
    sf::VertexArray connections(sf::Lines);
    for (auto& connection: m_Connections)
    {
        auto& start = m_Nodes.at(connection.start);
        auto& end = m_Nodes.at(connection.end);
        connections.append(sf::Vertex(start->GetPosition(), sf::Color::Black));
        connections.append(sf::Vertex(end->GetPosition(), sf::Color::Black));
    }
    // render current connection being drawn
    if (m_CurrentParentNode >= 0)
    {
        auto& start = m_Nodes.at(m_CurrentParentNode);
        connections.append(sf::Vertex(start->GetPosition(), sf::Color::Black));
        connections.append(sf::Vertex(GetMousePosFloat(m_Window), sf::Color::Black));
    }
    m_Window.draw(connections);
    // imgui
    RenderImGui(); 
    ImGui::SFML::Render(m_Window);
    m_Window.display();
}

void BodyCreator::RenderImGui()
{
    static sf::Clock imguiClock;
    static char buffer[100] = {0};
    static sf::Vector2u resolution(m_Width, m_Height);
    ImGui::SFML::Update(m_Window, imguiClock.restart());
    ImGui::Begin("Info");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    // creator panel
    ImGui::Begin("Creator Panel");
    ImGui::InputText("Save location", buffer, 100);
    if (ImGui::Button("Save"))
    {
        SaveBody(buffer);
    }
    ImGui::Separator();
    ImGui::SFML::SliderVec2u("Resolution", resolution, sf::Vector2u(0, 1920), sf::Vector2u(0, 1080));
    if (ImGui::Button("Save resolution"))
    {
        m_Width = resolution.x;
        m_Height = resolution.y;
        m_Window.create(sf::VideoMode(m_Width, m_Height), "Soft Body Creator");
    }
    if (ImGui::Button("Reset"))
    {
        Reset();
    }
    ImGui::End();
    // get node panel
    for (auto& node: m_Nodes)
    {
        if (node->IsSelected())
        {   
            node->OnImguiRender();
            break;
        }
    }
};