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
    if (!m_IsSimulating)
        m_Window.draw(m_StaticBody);
    else
        m_Window.draw(m_Body);
    RenderImGui(); 
    ImGui::SFML::Render(m_Window);
    m_Window.display();
}

void BodyCreator::RenderImGui()
{
    static sf::Clock imguiClock;
    static char buffer[100] = "resources/";
    ImGui::SFML::Update(m_Window, imguiClock.restart());
    // basic info
    ImGui::Begin("Info");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    // creator panel
    ImGui::Begin("Creator Panel");
    ImGui::InputText("Location", buffer, 100);
    if (ImGui::Button("Save"))
        SaveBody(buffer);
    if (ImGui::Button("Load"))
        LoadBody(buffer);
    if (ImGui::Button("Toggle Simulation"))
        ToggleSimulation();
    ImGui::Separator();
    sf::Vector2u resolution(m_Width, m_Height);
    ImGui::SFML::SliderVec2u("Resolution", resolution, sf::Vector2u(0, 1920), sf::Vector2u(0, 1080));
    if (ImGui::Button("Save resolution"))
    {
        m_Width = resolution.x;
        m_Height = resolution.y;
        m_Window.create(sf::VideoMode(m_Width, m_Height), "Soft Body Creator");
    }
    ImGui::End();
    // body panels
    if (!m_IsSimulating)
    {
        ImGui::Begin("Static body");
        m_StaticBody.OnImGuiRender();
        ImGui::End();
    }
    else
    {
        ImGui::Begin("Simulation parameters");
        ImGui::SliderFloat("Gravity", &m_Gravity, -100, 100);
        m_Body.OnImGuiRender();
        ImGui::End();
    }
};