#pragma once

#include <SFML/Graphics.hpp>

namespace ImGui
{
namespace SFML
{
bool SliderVec2f(const char* label, sf::Vector2f& v, const sf::Vector2f& xRange, const sf::Vector2f& yRange);
}
}