#include "App.hpp"
#include "Body/Body.hpp"
#include "Body/Joint.hpp"

#include <memory>

#include <string>
#include <fstream>
#include <sstream>
#include <istream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <imgui-sfml/imgui-SFML.h>

#include "AppConfig.h"

App::App(const std::string& levelPath)
    : m_Width(DEFAULT_WIDTH), m_Height(DEFAULT_HEIGHT), m_Fps(DEFAULT_FPS),
      m_Window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), PROJECT_NAME), 
      m_RngEngine(time(NULL)),
      m_Gravity(DEFAULT_GRAVITY),
      m_Bodies(0)
{
    LoadLevelFromFile(levelPath);
    ImGui::SFML::Init(m_Window);
}

void App::LoadLevelFromFile(const std::string& levelPath)
{
    std::ifstream filestream(levelPath);
    if (!filestream)
    {
        std::cout << "Couldn't open level file: " << levelPath << std::endl;
        return;
    }
    std::string buffer;
    std::stringstream values;
    bool resolutionChanged = false;
    unsigned int pos = 0;

    while (getline(filestream, buffer))
    {   
        values.clear();
        if ((pos = buffer.find("width")) != std::string::npos) 
        {   
            values << buffer.substr(pos+5);
            values >> m_Width;
            resolutionChanged = true;
        }
        else if ((pos = buffer.find("height")) != std::string::npos)
        {
            values << buffer.substr(pos+6);
            values >> m_Height;
            resolutionChanged = true;
        }
        else if ((pos = buffer.find("fps")) != std::string::npos)
        {
            values << buffer.substr(pos+3);
            values >> m_Fps;
            m_Window.setFramerateLimit(m_Fps);
        }
        else if ((pos = buffer.find("gravity")) != std::string::npos)
        {
            values << buffer.substr(pos+7);
            values >> m_Gravity;
        }
        else if ((pos = buffer.find("body")) != std::string::npos)
        {
            std::string filename;
            values << buffer.substr(pos+4);
            values >> filename;
            std::ifstream bodyFilestream(filename);
            std::shared_ptr<Body> body = std::make_shared<Body>();
            bodyFilestream >> *body;
            m_Bodies.push_back(body);
        }
    } 
    if (resolutionChanged)
        m_Window.create(sf::VideoMode(m_Width, m_Height), "Soft Body Physics");
}