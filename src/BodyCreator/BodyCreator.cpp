#include "BodyCreator.hpp"
#include "DragableBodyNode.hpp"
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>

#include <imgui-sfml/imgui-SFML.h>

BodyCreator::BodyCreator(unsigned int width, unsigned int height, unsigned int fps)
    : m_Width(width), m_Height(height), m_Fps(fps),
      m_Nodes(0), m_Connections(0), m_CurrentParentNode(-1),
      m_Window(sf::VideoMode(width, height), "Body Creator")
{
    m_Window.setFramerateLimit(fps);
    ImGui::SFML::Init(m_Window);
}

void BodyCreator::Run()
{
    sf::Thread updateThread(std::bind(&Update, this));
    updateThread.launch();

    sf::Time lastUpdate = m_Clock.getElapsedTime();
    int frameTime = 1000/(float)m_Fps;
    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > frameTime)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            Render();
            PollEvents();
            m_Mutex.unlock();
        }
    }
}

void BodyCreator::Update()
{
    sf::Time lastUpdate = m_Clock.getElapsedTime();
    float updateTime = 1000.0f/(float)m_Fps;

    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > updateTime)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            for (auto& node: m_Nodes)
            {
                node->Update(&m_Window);
            }
            m_Mutex.unlock();
        }
    }
}


