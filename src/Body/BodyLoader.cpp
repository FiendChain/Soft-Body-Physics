#include <fstream>
#include <sstream>
#include <istream>
#include <iostream>
#include "Body.hpp"

// loading
std::istream& operator >>(std::istream& in, Body& body)
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
            Joint joint(mass, radius);
            joint.SetPosition(posX, posY);
            body.AddJoint(joint);
        }
        else if ((pos = buffer.find("s ")) != std::string::npos)
        {
            values << buffer.substr(pos+1);
            float k, c, length;
            unsigned int start, end;
            values >> k >> c >> length >> start >> end;
            body.AddConnection({k, c, length, start, end});
        }
    }

    return in;
}

// saving
std::ostream& operator <<(std::ostream& out, Body& body)  
{
    if (!out)
    {
        std::cerr << "Can't save body to file, doesn't exists" << std::endl;
        return out;
    }

    for (auto& joint: body.m_Joints)
    {
        sf::Vector2f position = joint.GetPosition();
        out << "    v "  << 
            joint.GetMass()     << " " << 
            joint.GetRadius()   << " " <<
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
            connection.end      << "\n";
    }
    return out;
}