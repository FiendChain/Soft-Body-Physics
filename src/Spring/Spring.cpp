#include "Spring.hpp"
#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML-addons.h>

Spring::Spring(float k, float mass, const sf::Vector2f& pivot, const sf::Vector2f& point)
    : m_Pivot(3), m_Particle(mass, 10),
      m_K(k)
{
    m_Pivot.SetPosition(pivot);
    m_Particle.SetPosition(point);
}

void Spring::Update(float deltaTime, sf::Window *window)
{
    // f = -k (x-x0)
    sf::Vector2f force = -m_K * (m_Particle.GetPosition() - m_Pivot.GetPosition());
    m_Particle.ApplyForce(force);
    m_Particle.Update(deltaTime, window);
    m_Pivot.Update(window);
}

bool Spring::OnEvent(const sf::Event& event)
{
    if (m_Particle.OnEvent(event)) return true;
    if (m_Pivot.OnEvent(event))    return true;
    return false;
}

void Spring::OnImGuiRender()
{
    ImGui::Begin("Spring");
    ImGui::SliderFloat("k", &m_K, 0, 20);
    ImGui::End();
}

void Spring::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Particle, states);
    target.draw(m_Pivot, states);
    // draw connection
    sf::VertexArray vertexes(sf::Lines);
    vertexes.append(sf::Vertex(m_Pivot.GetPosition(), sf::Color::Black));
    vertexes.append(sf::Vertex(m_Particle.GetPosition(), sf::Color::Black));
    target.draw(vertexes, states);
}

// forces and acceleration
void Spring::ApplyForce(const sf::Vector2f& force)
{
    m_Particle.ApplyForce(force);
}

void Spring::ApplyForce(float x, float y)
{
    m_Particle.ApplyForce(x, y);
}

void Spring::ApplyAcceleration(const sf::Vector2f& acceleration)
{
    m_Particle.ApplyAcceleration(acceleration);
}

void Spring::ApplyAcceleration(float x, float y)
{
    m_Particle.ApplyAcceleration(x, y);
}