#include "Body.hpp"
#include "StaticBody/StaticBody.hpp"

Body& Body::operator =(StaticBody& body)
{
    m_Joints.erase(m_Joints.begin(), m_Joints.end());
    m_Connections.erase(m_Connections.begin(), m_Connections.end());
    for (auto& staticJoint: body.GetJoints()) 
    {
        Joint joint(staticJoint->GetMass(), staticJoint->GetRadius());
        joint.SetPosition(staticJoint->GetPosition()); 
        AddJoint(joint);
    }
    for (auto& connection: body.GetConnections())
    {
        AddConnection(connection);
    }
    return *this;
} 