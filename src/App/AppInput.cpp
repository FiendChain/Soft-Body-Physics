#include "App.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-sfml/imgui-SFML.h>

void App::PollEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        m_Body.OnEvent(event);
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {

            }
        }
    }
}