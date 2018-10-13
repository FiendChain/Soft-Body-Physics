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
    m_Window.draw(m_StaticBody);
    RenderImGui(); 
    ImGui::SFML::Render(m_Window);
    m_Window.display();
}

void BodyCreator::PollEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        m_StaticBody.OnEvent(event);
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
    }
}

void BodyCreator::RenderImGui()
{
    static sf::Clock imguiClock;
    static char buffer[100] = {0};
    ImGui::SFML::Update(m_Window, imguiClock.restart());
    // basic info
    ImGui::Begin("Info");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    // creator panel
    ImGui::Begin("Creator Panel");
    m_Body.OnImGuiRender();
    ImGui::InputText("Save location", buffer, 100);
    if (ImGui::Button("Save"))
    {
        SaveBody(buffer);
    }
    ImGui::Separator();
    sf::Vector2u resolution(m_Width, m_Height);
    ImGui::SFML::SliderVec2u("Resolution", resolution, sf::Vector2u(0, 1920), sf::Vector2u(0, 1080));
    if (ImGui::Button("Save resolution"))
    {
        m_Width = resolution.x;
        m_Height = resolution.y;
        m_Window.create(sf::VideoMode(m_Width, m_Height), "Soft Body Creator");
    }
};