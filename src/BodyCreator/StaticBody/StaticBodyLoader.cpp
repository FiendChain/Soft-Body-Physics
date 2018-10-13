#include "StaticBody.hpp"

#include <istream>
#include <ostream>

std::istream& operator >>(std::istream& in, StaticBody& body)
{
    if (!in)
        return in;
    return in;
}

std::ostream& operator <<(std::ostream& out, StaticBody& body)
{
    if (!out)
        return out;
    for (auto& joint: body.m_Joints)
    {
        sf::Vector2f position = joint->GetPosition();
        out << "    v "  << 
            joint->GetMass()     << " " << 
            joint->GetRadius()   << " " <<
            position.x          << " " << 
            position.y          << "\n";
    }
    for (auto& connection: body.m_Connections)
    {
        out << "    s "  <<
            connection.k        << " " <<
            connection.c        << " " <<
            connection.length   << " " <<
            connection.start    << " " << 
            connection.end      << " \n";
    }
    return out;
}
