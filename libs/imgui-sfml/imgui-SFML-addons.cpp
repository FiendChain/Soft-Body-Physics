#include <SFML/Graphics.hpp>
#include "imgui-SFML-addons.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGui
{

namespace SFML
{
bool SliderVec2f(const char* label, sf::Vector2f& v, const sf::Vector2f& xRange, const sf::Vector2f& yRange)
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
    value_changed |= SliderScalar("##v", ImGuiDataType_Float, &v.x, &xRange.x, &xRange.y);
    SameLine(0, g.Style.ItemInnerSpacing.x);
    PopID();
    PopItemWidth();

    PushID(1);
    value_changed |= SliderScalar("##v", ImGuiDataType_Float, &v.y, &yRange.x, &yRange.y);
    SameLine(0, g.Style.ItemInnerSpacing.x);
    PopID();
    PopItemWidth();

    PopID();

    TextUnformatted(label, FindRenderedTextEnd(label));
    EndGroup();
    return value_changed;
}
}

}