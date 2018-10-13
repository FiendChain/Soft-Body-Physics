#include <fstream>
#include <sstream>
#include <istream>
#include <iostream>
#include "Body.hpp"

// loading
std::istream& operator >>(std::istream& filestream, Body& body)
{
    if (!filestream)
    {
        std::cerr << "Can't load body from file, doesn't exists" << std::endl;
        return filestream;
    }

    std::string buffer;
    std::stringstream values;
    unsigned int pos = 0;

    while (getline(filestream, buffer))
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

    return filestream;
}

// saving
std::ostream& operator <<(std::ostream& filestream, Body& body)  
{
    if (!filestream)
    {
        std::cerr << "Can't save body to file, doesn't exists" << std::endl;
        return filestream;
    }

    for (auto& joint: body.m_Joints)
    {
        sf::Vector2f position = joint.GetPosition();
        filestream << "    v "  << 
            joint.GetMass()     << " " << 
            joint.GetRadius()   << " " <<
            position.x          << " " << 
            position.y          << "\n";
    }
    for (auto& connection: body.m_Connections)
    {
        filestream << "    s "  <<
            connection.k        << " " <<
            connection.c        << " " <<
            connection.length   << " " <<
            connection.start    << " " << 
            connection.end      << "\n";
    }
    return filestream;
}