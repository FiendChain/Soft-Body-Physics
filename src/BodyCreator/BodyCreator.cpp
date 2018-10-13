#include "BodyCreator.hpp"
#include "StaticBody/StaticBody.hpp"
#include <SFML/Graphics.hpp>

#include <functional>
#include <iostream>

#include <sstream>
#include <fstream>

#include <imgui-sfml/imgui-SFML.h>

BodyCreator::BodyCreator(unsigned int width, unsigned int height, unsigned int fps)
    : m_Width(width), m_Height(height), m_Fps(fps),
      m_IsSimulating(false), m_Gravity(9.8f),
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
    float deltaTime = 1.0f/(float)m_Fps;
    std::function<void(Joint&)> collideWall = [this](Joint &joint) {
        sf::Vector2f pos = joint.GetPosition();
        sf::Vector2f vel = joint.GetVelocity();
        if (pos.x < 0) 
        {
            pos.x = 0;
            vel.x = 0;
        }
        else if (pos.x > m_Width) 
        {   
            pos.x = m_Width;
            vel.x = 0;
        }
        if (pos.y < 0)
        {
            pos.y = 0;
            vel.y = 0;
        }
        else if (pos.y > m_Height)
        {
            pos.y = m_Height;
            vel.y = 0;
        }
        joint.SetPosition(pos);
        joint.SetVelocity(vel);
    };

    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > updateTime)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            if (!m_IsSimulating)
            {
                m_StaticBody.Update(deltaTime, &m_Window);
            }
            else
            {
                m_Body.ApplyAcceleration(0, m_Gravity);
                m_Body.ApplyPhysicsToJoints(collideWall);
                m_Body.Update(deltaTime, &m_Window);
            }
            m_Mutex.unlock();
        }
    }
}

void BodyCreator::ToggleSimulation()
{
    if (!m_IsSimulating)
    {
        m_Body = m_StaticBody; 
        m_IsSimulating = true;
    }
    else
    {
        m_IsSimulating = false;
    }
}

void BodyCreator::LoadBody(const std::string& filepath)
{
    std::ifstream filestream(filepath);
    m_StaticBody.Reset();
    filestream >> m_StaticBody;
}

void BodyCreator::SaveBody(const std::string& filepath)
{
    std::ofstream filestream(filepath);
    filestream << m_StaticBody;
}


