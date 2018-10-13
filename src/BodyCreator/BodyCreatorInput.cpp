#include "BodyCreator.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-sfml/imgui-SFML.h>

void BodyCreator::PollEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        for (auto& node: m_Nodes)
        {
            node->OnEvent(event);
        }
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f position(event.mouseButton.x, event.mouseButton.y);
                if (RemoveBody(position)) {}    // remove a body if lctrl is held
                else if (m_CurrentParentNode < 0 && StartConnection(position)) {}   // start if lalt is held
                else if (m_CurrentParentNode >= 0 && CreateConnection(position)) {} // on click if current node exists
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Tab:
                AddBody();
                break;
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
}