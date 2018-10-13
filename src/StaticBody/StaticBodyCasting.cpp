#include "StaticBody.hpp"
#include "Body/Body.hpp"
#include "Body/Joint.hpp"

void StaticBody::CastToBody(Body& body)
{
    for (auto& staticJoint: m_Joints)
    {
        Joint joint(staticJoint->GetMass(), staticJoint->GetRadius());
        joint.SetPosition(staticJoint->GetPosition());
        body.AddJoint(joint);
    }
    for (auto& connection: m_Connections)
    {
        body.AddConnection(connection);
    }
    
}