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
        unsigned int m_Width, m_Height, m_Fps;
        sf::Clock m_Clock;
        sf::Mutex m_Mutex;
        Body m_Body; // simulation
        StaticBody m_StaticBody;
        bool m_IsSimulating;
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