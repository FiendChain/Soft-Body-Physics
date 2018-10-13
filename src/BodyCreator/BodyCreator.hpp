#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

#include "Body/Body.hpp"
#include "DragableBodyNode.hpp"

class BodyCreator
{
    private:
        sf::RenderWindow m_Window;
        unsigned int m_Width, m_Height, m_Fps;
        sf::Clock m_Clock;
        sf::Mutex m_Mutex;
        int m_CurrentParentNode;
        std::vector<std::shared_ptr<DragableBodyNode>> m_Nodes;
        std::vector<Body::Connection> m_Connections;
    public:
        BodyCreator(unsigned int width, unsigned int height, unsigned int fps);
        void Run();
    private:
        void PollEvents();
        void Render();
        void RenderImGui();
        void Update(); 
        void Reset();
        bool CreateConnection(const sf::Vector2f& position); // connections
        bool StartConnection(const sf::Vector2f& position);
        void AddBody();
        bool RemoveBody(const sf::Vector2f& position);
        void SaveBody(const std::string& path);
};