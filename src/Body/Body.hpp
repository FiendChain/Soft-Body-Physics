#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Joint.hpp"
#include "InteractableEntity.hpp"

class Body: public InteractableEntity
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
        virtual void Update(float deltaTime, sf::Window *window) override;
        void ApplyAcceleration(const sf::Vector2f& acceleration);
        void ApplyAcceleration(float x, float y);
        void ApplyPhysicsToJoints(const std::function<void(Joint&)>& func);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void ApplyInternalForces();
};