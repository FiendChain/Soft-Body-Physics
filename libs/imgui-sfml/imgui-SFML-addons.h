#pragma once

#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>

namespace ImGui
{
namespace SFML
{

template <typename T, ImGuiDataType_ U>
bool SliderVec2(const char* label, sf::Vector2<T>& v, const sf::Vector2<T>& xRange, const sf::Vector2<T>& yRange);



auto const SliderVec2f = &SliderVec2<float, ImGuiDataType_Float>;
auto const SliderVec2u = &SliderVec2<unsigned int, ImGuiDataType_U32>;
auto const SliderVec2i = &SliderVec2<int, ImGuiDataType_S32>;
}
}