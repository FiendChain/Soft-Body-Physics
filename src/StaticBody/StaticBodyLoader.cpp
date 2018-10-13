#include "StaticBody.hpp"
#include <iostream>
#include <istream>
#include <sstream>
#include <ostream>
#include <memory>

std::istream& operator >>(std::istream& in, StaticBody& body)
{
    if (!in)
    {
        std::cerr << "Can't load body from file, doesn't exists" << std::endl;
        return in;
    }

    std::string buffer;
    std::stringstream values;
    unsigned int pos = 0;

    while (getline(in, buffer))
    {   
        values.clear();
        if ((pos = buffer.find("v ")) != std::string::npos)
        {
            values << buffer.substr(pos+1);
            float mass, radius, posX, posY;
            values >> mass >> radius >> posX >> posY;
            std::shared_ptr<StaticJoint> joint = std::make_shared<StaticJoint>(radius, mass);
            joint->SetPosition(posX, posY);
            body.m_Joints.push_back(joint);
            
        }
        else if ((pos = buffer.find("s ")) != std::string::npos)
        {
            values << buffer.substr(pos+1);
            float k, c, length;
            unsigned int start, end;
            values >> k >> c >> length >> start >> end;
            body.m_Connections.push_back({k, c, length, start, end});
        }
    }
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
