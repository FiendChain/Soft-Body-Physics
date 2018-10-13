// methods for edition the body
#include "BodyCreator.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

void BodyCreator::Reset()
{
    m_Connections.erase(m_Connections.begin(), m_Connections.end());
    m_Nodes.erase(m_Nodes.begin(), m_Nodes.end());
    m_CurrentParentNode = -1;
}

bool BodyCreator::CreateConnection(const sf::Vector2f& position) 
{
    if (m_CurrentParentNode < 0)
        return false;

    for (unsigned int i = 0; i < m_Nodes.size(); i++)
    {
        auto& node = m_Nodes.at(i);
        if (i != m_CurrentParentNode && node->CheckPositionInside(position))
        {
            Body::Connection connection = {1,1,-1,m_CurrentParentNode,i};
            m_Connections.push_back(connection);
            m_CurrentParentNode = -1;
            return true;
        }
    }
    m_CurrentParentNode = -1;
    return false;
}

bool BodyCreator::StartConnection(const sf::Vector2f& position)
{
    if (m_CurrentParentNode >= 0) 
        return false;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return false;

    for (unsigned int i = 0; i < m_Nodes.size(); i++)
    {
        auto& node = m_Nodes.at(i);
        if (node->CheckPositionInside(position))
        {
            m_CurrentParentNode = i;
            return true;
        }
    }
    m_CurrentParentNode = -1;
    return false;
}

void BodyCreator::AddBody()
{
    std::shared_ptr<DragableBodyNode> node = std::make_shared<DragableBodyNode>(10);
    sf::Vector2i pos = sf::Mouse::getPosition(m_Window);
    sf::Vector2f mousePos(pos.x, pos.y);
    node->SetPosition(mousePos);
    m_Nodes.push_back(node);
}

bool BodyCreator::RemoveBody(const sf::Vector2f& position)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        return false;
    }
    for (unsigned int i = 0; i < m_Nodes.size(); i++)
    {
        auto& node = m_Nodes.at(i);
        if (node->CheckPositionInside(position))
        {
            m_Nodes.erase(m_Nodes.begin()+i);
            for (unsigned int j = 0; j < m_Connections.size(); j++)
            {
                auto& connection = m_Connections.at(j);
                // if any connection is using the deleted node, remove it
                if (connection.start == i || connection.end == i)
                {
                    m_Connections.erase(m_Connections.begin()+j);
                    j--;
                } 
                // connections that use nodes proceeding the delete node should
                // have their associated index decremented
                else
                {
                    if (connection.start > i) connection.start--;
                    if (connection.end > i)   connection.end--;
                }
            }
            return true;
        }
    }
    return false;
}

void BodyCreator::SaveBody(const std::string& path)
{
    std::stringstream buffer;
    buffer << "resources/" << path << ".body";
    std::ofstream filestream(buffer.str());
    if (!filestream)
    {

        std::cerr << "Failed to export body to " << buffer.str() << std::endl;
        return;
    }

    for (auto& node: m_Nodes)
    {
        sf::Vector2f position = node->GetPosition();
        filestream << "    v "  << 
            node->GetMass()     << " " << 
            node->GetRadius()   << " " <<
            position.x          << " " << 
            position.y          << "\n";
    }
    for (auto& connection: m_Connections)
    {
        filestream << "    s "  <<
            connection.k        << " " <<
            connection.c        << " " <<
            connection.length   << " " <<
            connection.start    << " " << 
            connection.end      << " \n";
    }
}