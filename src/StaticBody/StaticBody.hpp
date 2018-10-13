#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <istream>
#include <fstream>

#include "Entities/Connection.hpp"
#include "Entities/InteractableEntity.hpp"
#include "StaticJoint.hpp"

class StaticBody: public InteractableEntity
{
    private:
        int m_CurrentParentNode;
        float m_JointRadius, m_JointMass;
        float m_K, m_C;
        std::vector<std::shared_ptr<StaticJoint>> m_Joints;
        std::vector<Connection> m_Connections;
    public:
        StaticBody();
        virtual bool OnEvent(const sf::Event& event) override;
        virtual void OnImGuiRender() override;
        virtual void Update(float deltaTime, sf::Window *window) override;
        void Reset();
        const auto& GetJoints() const { return m_Joints; }
        const auto& GetConnections() const { return m_Connections; }
    private:
        bool CreateConnection(const sf::Vector2f& position); // connections
        bool StartConnection(const sf::Vector2f& position);
        bool AddJoint(const sf::Vector2f& position);
        bool RemoveJoint(const sf::Vector2f& position);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        friend std::istream& operator >>(std::istream& in, StaticBody& body);
        friend std::ostream& operator <<(std::ostream& out, StaticBody& body);
};