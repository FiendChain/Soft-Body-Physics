#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <istream>
#include <ostream>
#include "Joint.hpp"
#include "Entities/InteractableEntity.hpp"
#include "StaticBody/StaticBody.hpp"
#include "Entities/Connection.hpp"

class Body: public InteractableEntity
{
    private:
        std::vector<Joint> m_Joints;
        std::vector<Connection> m_Connections;
    public:
        Body();
        Body(const std::vector<Joint>& joints, const std::vector<Connection>& connections);
        void AddJoint(const Joint& joint);
        void AddConnection(const Connection& connection);
        virtual void Update(float deltaTime, sf::Window *window) override;
        virtual bool OnEvent(const sf::Event& event) override;
        void ApplyAcceleration(const sf::Vector2f& acceleration);
        void ApplyAcceleration(float x, float y);
        void ApplyPhysicsToJoints(const std::function<void(Joint&)>& func);
        Body& operator =(StaticBody& body);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void ApplyInternalForces();
    public:
        friend std::istream& operator >>(std::istream& in, Body& body);
        friend std::ostream& operator <<(std::ostream& out, Body& body);
};