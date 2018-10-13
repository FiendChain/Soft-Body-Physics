#include <SFML/Graphics.hpp>
#include "imgui-SFML-addons.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGui
{

namespace SFML
{

template <typename T, ImGuiDataType_ U>
bool SliderVec2(const char* label, sf::Vector2<T>& v, const sf::Vector2<T>& xRange, const sf::Vector2<T>& yRange)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    bool value_changed = false;
    BeginGroup();
    PushID(label);
    PushMultiItemsWidths(2);

    PushID(0);
    value_changed |= SliderScalar("##v", U, &v.x, &xRange.x, &xRange.y);
    SameLine(0, g.Style.ItemInnerSpacing.x);
    PopID();
    PopItemWidth();

    PushID(1);
    value_changed |= SliderScalar("##v", U, &v.y, &yRange.x, &yRange.y);
    SameLine(0, g.Style.ItemInnerSpacing.x);
    PopID();
    PopItemWidth();

    PopID();

    TextUnformatted(label, FindRenderedTextEnd(label));
    EndGroup();
    return value_changed;
}

template bool SliderVec2<float, ImGuiDataType_Float>(const char *, sf::Vector2<float>&, const sf::Vector2<float>&, const sf::Vector2<float>&);
template bool SliderVec2<unsigned int, ImGuiDataType_U32>(const char *, sf::Vector2<unsigned int>&, const sf::Vector2<unsigned int>&, const sf::Vector2<unsigned int>&);
template bool SliderVec2<int, ImGuiDataType_S32>(const char *, sf::Vector2<int>&, const sf::Vector2<int>&, const sf::Vector2<int>&);
}

}