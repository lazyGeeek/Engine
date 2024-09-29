#include "ui/panels/undecorated_panel.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Panels
{
    void UndecoratedPanel::DrawImpl()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 previousPadding = style.WindowPadding;
        ImVec2 previousMinSize = style.WindowMinSize;

        style.WindowPadding = { 0, 0 };
        style.WindowMinSize = { 0, 0 };

        if (ImGui::Begin(m_panelId.c_str(), nullptr, collectFlags()))
        {
            style.WindowPadding = previousPadding;
            style.WindowMinSize = previousMinSize;

            Update();
            DrawWidgets();

            ImGui::End();
        }
        else
        {
            style.WindowPadding = previousPadding;
        }
    }

    int UndecoratedPanel::collectFlags()
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysUseWindowPadding |
                                 ImGuiWindowFlags_NoResize               |
                                 ImGuiWindowFlags_NoMove                 |
                                 ImGuiWindowFlags_NoScrollbar            |
                                 ImGuiWindowFlags_NoScrollWithMouse      |
                                 ImGuiWindowFlags_NoCollapse             |
                                 ImGuiWindowFlags_NoTitleBar             |
                                 ImGuiWindowFlags_NoBackground;

        if (m_autoSize) flags |= ImGuiWindowFlags_AlwaysAutoResize;

        return flags;
    }
}
