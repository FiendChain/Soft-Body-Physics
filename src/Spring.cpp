#include "Spring.hpp"
#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML-addons.h>

Spring::Spring(float k, float mass, const sf::Vector2f& pivot, const sf::Vector2f& point)
    : m_Pivot(3), m_Particle(mass, 10),
      m_K(k),
      m_DragPivot(false), m_DragParticle(false)
{
    // pivot
    m_Pivot.setPosition(pivot);
    m_Pivot.setOrigin(3, 3);
    m_Pivot.setFillColor(sf::Color::Red);
    m_Pivot.setOutlineColor(sf::Color::Black);
    m_Pivot.setOutlineThickness(2.0f);
    // outline box
    m_OutlineBox.setFillColor(sf::Color::Transparent);
    m_OutlineBox.setOutlineColor(sf::Color::Green);
    m_OutlineBox.setOutlineThickness(1.0f);

    m_Particle.setPosition(point);
}

void Spring::Update(float deltaTime, sf::Window *window)
{
    // f = -k (x-x0)
    sf::Vector2f force = -m_K * (m_Particle.getPosition() - m_Pivot.getPosition());
    m_Particle.ApplyForce(force);
    m_Particle.Update(deltaTime);
    // drag pivot or particle
    if (m_DragPivot || m_DragParticle)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);
        m_OutlineBox.setPosition(mousePosFloat);
        if (m_DragParticle)
        {
            // v = d/t
            sf::Vector2f velocity = (mousePosFloat - m_Particle.getPosition()) / deltaTime;
            m_Particle.SetVelocity(velocity);
        }
        else if (m_DragPivot) 
        {
            m_Pivot.setPosition(mousePosFloat);
        }
    }
}

bool Spring::OnEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            return SelectItem(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            m_DragParticle = m_DragPivot = false;
        }
    }
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
    vertexes.append(sf::Vertex(m_Pivot.getPosition(), sf::Color::Black));
    vertexes.append(sf::Vertex(m_Particle.getPosition(), sf::Color::Black));
    target.draw(vertexes, states);
    // draw box
    if (m_DragPivot || m_DragParticle) 
        target.draw(m_OutlineBox, states);
}

bool Spring::SelectItem(const sf::Vector2f& clickPos)
{
    // pivot
    sf::Vector2f posDiff = m_Pivot.getPosition() - clickPos;
    float distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    if (distanceSquared < m_Pivot.getRadius()*m_Pivot.getRadius())
    {
        m_DragPivot = true;
        sf::Vector2f size = sf::Vector2f(m_Pivot.getRadius(), m_Pivot.getRadius()) * 1.1f;
        m_OutlineBox.setSize(size*2.0f);
        m_OutlineBox.setOrigin(size);
        return true;
    }
    // particle
    posDiff = m_Particle.getPosition() - clickPos;
    distanceSquared = posDiff.x*posDiff.x + posDiff.y*posDiff.y;
    if (distanceSquared < m_Particle.getRadius()*m_Particle.getRadius())
    {
        m_DragParticle = true;
        sf::Vector2f size = sf::Vector2f(m_Particle.getRadius(), m_Particle.getRadius()) * 1.1f;
        m_OutlineBox.setSize(size*2.0f);
        m_OutlineBox.setOrigin(size);
        return true;
    }
    m_DragParticle = m_DragPivot = false;
    return false;
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