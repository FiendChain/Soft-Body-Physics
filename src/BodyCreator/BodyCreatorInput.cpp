#include "BodyCreator.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-sfml/imgui-SFML.h>
#include <iostream>

void BodyCreator::PollEvents()
{
    sf::Event event;
    static float zoom = 1.0f;
    while (m_Window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (!m_IsSimulating)
            m_StaticBody.OnEvent(event);
        else
            m_Body.OnEvent(event);
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            m_Width = event.size.width;
            m_Height = event.size.height;
            sf::FloatRect visibleArea(0, 0, m_Width, m_Height);
            m_Window.setView(sf::View(visibleArea));
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.delta < 0)
            {
                zoom *= 0.98f;
                m_View.zoom(zoom);
                m_Window.setView(m_View);
            }
            else 
            {
                zoom *= 1.2f;
                m_View.zoom(zoom);
                m_Window.setView(m_View);
            }
        }
    }
}