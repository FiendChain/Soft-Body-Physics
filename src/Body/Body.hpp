#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Joint.hpp"

class Body: public sf::Drawable
{
    public:
        struct Connection
        {
            float k;            // spring coefficient
            float length;
            unsigned int start; // connections
            unsigned int end;
        };
    private:
        std::vector<Joint> m_Joints;
        std::vector<Connection> m_Connections;
    public:
        Body();
        Body(const std::vector<Joint>& joints, const std::vector<Connection>& connections);
        void AddJoint(const Joint& joint);
        void AddConnection(const Connection& connection);
        void Update(float deltaTime);
        void ApplyAcceleration(const sf::Vector2f& acceleration);
        void ApplyAcceleration(float x, float y);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void ApplyInternalForces();
};