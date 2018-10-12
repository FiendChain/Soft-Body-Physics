#pragma once
#include <SFML/Graphics.hpp>

class InteractableEntity: public sf::Drawable
{
    public:
        InteractableEntity();
        virtual bool OnEvent(const sf::Event& event);
        virtual void OnImGuiRender();
        virtual void Update(float deltaTime, sf::Window *window);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};