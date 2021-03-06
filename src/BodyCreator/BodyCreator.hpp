#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

#include "Body/Body.hpp" 
#include "StaticBody/StaticBody.hpp"

class BodyCreator
{
    private:
        sf::RenderWindow m_Window;
        sf::View m_View;
        unsigned int m_Width, m_Height, m_Fps;
        sf::Clock m_Clock;
        sf::Mutex m_Mutex;
        Body m_Body; 
        StaticBody m_StaticBody;
        bool m_IsSimulating; // simulation
        float m_Gravity;
    public:
        BodyCreator(unsigned int width, unsigned int height, unsigned int fps);
        void Run();
    private:
        void PollEvents();
        void Render();
        void RenderImGui();
        void Update();
        void ToggleSimulation();
        void LoadBody(const std::string& filepath);
        void SaveBody(const std::string& filepath);
};