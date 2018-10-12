#include "Body.hpp"
#include "Joint.hpp"
#include <SFML/Graphics.hpp>

Body::Body()
    : m_Joints(0), m_Connections(0)
{

}

Body::Body(const std::vector<Joint>& joints, const std::vector<Connection>& connections)
    : m_Joints(joints),
      m_Connections(connections)
{
    
}

void Body::AddJoint(const Joint& joint)
{
    m_Joints.push_back(joint);
}

void Body::AddConnection(const Connection& connection)
{
    m_Connections.push_back(connection);
}

void Body::Update(float deltaTime)
{

}

void Body::ApplyAcceleration(const sf::Vector2f& acceleration)
{

}

void Body::ApplyAcceleration(float x, float y)
{

}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}