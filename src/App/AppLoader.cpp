#include "App.hpp"
#include "Body/Body.hpp"
#include "Body/Joint.hpp"

#include <memory>

#include <string>
#include <fstream>
#include <sstream>
#include <istream>

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
    try {
        LoadLevelFromFile(levelPath);
    } catch(...) {
        std::stringstream error;
        error << "Couldn't load level file: " << levelPath;
        throw std::runtime_error(error.str());
    }
    ImGui::SFML::Init(m_Window);
}

void App::LoadLevelFromFile(const std::string& levelPath)
{
    std::ifstream filestream(levelPath);
    if (!filestream)
    {
        std::stringstream error;
        error << "Couldn't open level file: " << levelPath;
        throw std::runtime_error(error.str());
    }
    std::string buffer;
    std::stringstream values;
    bool resolutionChanged = false;
    bool parsingBody = false;
    unsigned int pos = 0;
    std::shared_ptr<Body> body;

    while (getline(filestream, buffer))
    {   
        values.clear();
        if (parsingBody)
        {
            if ((pos = buffer.find("v ")) != std::string::npos)
            {
                values << buffer.substr(pos+1);
                float mass, radius, posX, posY;
                values >> mass >> radius >> posX >> posY;
                Joint joint(mass, radius);
                joint.setPosition(posX, posY);
                body->AddJoint(joint);
            }
            else if ((pos = buffer.find("s ")) != std::string::npos)
            {
                values << buffer.substr(pos+1);
                float k, c, length;
                unsigned int start, end;
                values >> k >> c >> length >> start >> end;
                body->AddConnection({k, c, length, start, end});
            }
            else
            {
                parsingBody = false;
                m_Bodies.push_back(body);
                body = nullptr;
            }
        }
        else if ((pos = buffer.find("width")) != std::string::npos) 
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
        else if (buffer.find("body:") != std::string::npos)
        {
            parsingBody = true;
            body = std::make_shared<Body>();
        }
    }
    if (body)
        m_Bodies.push_back(body);
    if (resolutionChanged)
        m_Window.create(sf::VideoMode(m_Width, m_Height), "Soft Body Physics");
}