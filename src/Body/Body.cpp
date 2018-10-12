#include "Body.hpp"
#include "Joint.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

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
    ApplyInternalForces();
    for (auto& joint: m_Joints) joint.Update(deltaTime);
}

void Body::ApplyInternalForces()
{
    for (auto& spring: m_Connections)
    {
        auto& start = m_Joints.at(spring.start);
        auto& end = m_Joints.at(spring.end);   
        sf::Vector2f posDiff = start.getPosition() - end.getPosition();
        float distance = pow(posDiff.x*posDiff.x + posDiff.y*posDiff.y, 0.5f);
        sf::Vector2f force = -spring.k * (distance-spring.length) * posDiff;
        start.ApplyForce(force);
        end.ApplyForce(-force); 
    }
}   

void Body::ApplyAcceleration(const sf::Vector2f& acceleration)
{
    for (auto& joint: m_Joints) joint.ApplyAcceleration(acceleration);
}

void Body::ApplyAcceleration(float x, float y)
{
    for (auto& joint: m_Joints) joint.ApplyAcceleration(x, y);
}

void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& joint: m_Joints) target.draw(joint, states);
    sf::VertexArray skeleton(sf::Lines);
    for (auto& spring: m_Connections)
    {
        auto& start = m_Joints.at(spring.start);
        auto& end = m_Joints.at(spring.end);
        skeleton.append(sf::Vertex(start.getPosition(), sf::Color::Black));
        skeleton.append(sf::Vertex(end.getPosition(), sf::Color::Black));
    }
    target.draw(skeleton, states);
}