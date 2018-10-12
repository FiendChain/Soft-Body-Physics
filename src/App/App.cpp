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
    for (auto& body: m_Bodies)
    {
        m_Window.draw(*body);
    }
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
    for (auto &body: m_Bodies)
        body->OnImGuiRender();
}

void App::Update()
{
    sf::Time lastUpdate = m_Clock.getElapsedTime();
    int updateTime = 1000.0f/(float)m_Fps; // implement tickrate later
    float deltaTime = 1.0f/(float)m_Fps;
    std::function<void(Joint&)> collideWall = [this](Joint &joint) {
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
    };

    while (m_Window.isOpen())
    {
        if ((m_Clock.getElapsedTime()-lastUpdate).asMilliseconds() > updateTime)
        {
            lastUpdate = m_Clock.getElapsedTime();
            m_Mutex.lock();
            for (auto& body: m_Bodies)
            {
                body->ApplyAcceleration(0, m_Gravity);
                body->ApplyPhysicsToJoints(collideWall);
                body->Update(deltaTime, &m_Window);
            }
            m_Mutex.unlock();
        }
    }
}