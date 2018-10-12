#include "App.hpp"
#include "Body/Body.hpp"
#include "AppConfig.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <time.h>
#include <functional>
#include <string>

#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

App::App(unsigned int width, unsigned int height, unsigned int fps)
    : m_Width(width), m_Height(height), m_Fps(fps), 
      m_Window(sf::VideoMode(width, height), PROJECT_NAME),
      m_RngEngine(time(NULL)),
      m_Gravity(9.8f)
{
    m_Window.setFramerateLimit(m_Fps);
    ImGui::SFML::Init(m_Window);
}

App::~App()
{

}

void App::Run()
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

void App::Render()
{
    // window
    m_Window.clear(sf::Color::White);
    m_Window.draw(m_Body);
    RenderImGui();
    ImGui::SFML::Render(m_Window);
    m_Window.display();
}

void App::RenderImGui()
{
    static sf::Clock imguiClock;
    ImGui::SFML::Update(m_Window, imguiClock.restart());
    ImGui::Begin("Info");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat("Gravity", &m_Gravity, -100, 100);
    ImGui::End();
    m_Body.OnImGuiRender();
}

void App::Update()
{
    sf::Time lastUpdate = m_Clock.getElapsedTime();
    int updateTime = 1000.0f/(float)m_Fps; // implement tickrate later
    float deltaTime = 1.0f/(float)m_Fps;

    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > updateTime)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            m_Body.ApplyAcceleration(0, m_Gravity);
            m_Body.ApplyPhysicsToJoints([this](Joint &joint) {
                sf::Vector2f pos = joint.getPosition();
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
                joint.setPosition(pos);
                joint.SetVelocity(vel);
            });
            m_Body.Update(deltaTime, &m_Window);
            m_Mutex.unlock();
        }
    }
}