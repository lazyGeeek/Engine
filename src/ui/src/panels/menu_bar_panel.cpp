#include "ui/panels/menu_bar_panel.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Panels
{
    void MenuBarPanel::DrawImpl()
    {
        //if (!m_widgets.empty() && ImGui::BeginMainMenuBar())
        //{
        //    DrawWidgets();
        //    ImGui::EndMainMenuBar();
        //}

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
    }
}
