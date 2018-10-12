#include "Body.hpp"
#include "Joint.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <functional>

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
    if (connection.length < 0)
    {
        Joint& start = m_Joints.at(connection.start);
        Joint& end = m_Joints.at(connection.end);
        sf::Vector2f posDiff = start.getPosition()-end.getPosition();
        float length = pow(posDiff.x*posDiff.x + posDiff.y*posDiff.y, 0.5f);
        m_Connections.push_back({
            connection.k, connection.c, length, connection.start, connection.end
        });
    }
    else 
    {
        m_Connections.push_back(connection);
    }
}

void Body::Update(float deltaTime, sf::Window *window)
{
    ApplyInternalForces();
    for (auto& joint: m_Joints) 
    {
        joint.Update(deltaTime, window);
    }
}

bool Body::OnEvent(const sf::Event& event)
{
    for (auto& joint: m_Joints)
    {
        if (joint.OnEvent(event)) return true;
    }
    return false;
}

void Body::ApplyPhysicsToJoints(const std::function<void(Joint&)>& func)
{
    for (auto& joint: m_Joints)
    {
        func(joint);
    }
}

void Body::ApplyInternalForces()
{
    for (auto& spring: m_Connections)
    {
        auto& start = m_Joints.at(spring.start);
        auto& end = m_Joints.at(spring.end);   
        sf::Vector2f posDiff = start.getPosition() - end.getPosition();
        sf::Vector2f velDiff = end.getPosition() - start.getPosition(); // relative velocity
        float distance = pow(posDiff.x*posDiff.x + posDiff.y*posDiff.y, 0.5f);
        // f = -k(x-x0) -c*v
        sf::Vector2f force = -spring.k * (distance-spring.length) * posDiff;
        force += -spring.c * velDiff;
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