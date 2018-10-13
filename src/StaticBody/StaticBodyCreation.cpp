#include "StaticBody.hpp"
#include <SFML/Graphics.hpp>

bool StaticBody::CreateConnection(const sf::Vector2f& position) // connection
{
    if (m_CurrentParentNode < 0)
        return false;

    for (unsigned int i = 0; i < m_Joints.size(); i++)
    {
        auto& joint = m_Joints.at(i);
        if (i != m_CurrentParentNode && joint->CheckPositionInside(position))
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

bool StaticBody::StartConnection(const sf::Vector2f& position)
{
    if (m_CurrentParentNode >= 0) 
        return false;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
        return false;

    for (unsigned int i = 0; i < m_Joints.size(); i++)
    {
        auto& joint = m_Joints.at(i);
        if (joint->CheckPositionInside(position))
        {
            m_CurrentParentNode = i;
            return true;
        }
    }
    m_CurrentParentNode = -1;
    return false;
}

bool StaticBody::AddJoint(const sf::Vector2f& position)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        return false;
    std::shared_ptr<StaticJoint> joint = std::make_shared<StaticJoint>(10, 10);
    joint->SetPosition(position);
    m_Joints.push_back(joint);
    return true;
}

bool StaticBody::RemoveJoint(const sf::Vector2f& position)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        return false;
    }
    for (unsigned int i = 0; i < m_Joints.size(); i++)
    {
        auto& joint = m_Joints.at(i);
        if (joint->CheckPositionInside(position))
        {
            m_Joints.erase(m_Joints.begin()+i);
            for (unsigned int j = 0; j < m_Connections.size(); j++)
            {
                auto& connection = m_Connections.at(j);
                // if any connection is using the deleted joint, remove it
                if (connection.start == i || connection.end == i)
                {
                    m_Connections.erase(m_Connections.begin()+j);
                    j--;
                } 
                // connections that use joints proceeding the delete joint should
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