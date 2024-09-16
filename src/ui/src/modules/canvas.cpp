#include "ui/modules/canvas.hpp"
#include "ui/panels/base_panel.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace Engine::UI::Modules
{
    void Canvas::RemovePanel(std::shared_ptr<Panels::BasePanel> panel)
    {
        auto& it = std::remove_if(m_panels.begin(), m_panels.end(), [&panel](std::shared_ptr<Panels::BasePanel>& item)
        {
            return panel == item;
        });

        if (it != m_panels.end())
            m_panels.erase(it, m_panels.end());
    }

    bool Canvas::Draw()
    {
        if (m_panels.empty())
            return false;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (m_isDockspace)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

            ImGui::Begin("##dockspace", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
            ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
            ImGui::SetWindowPos({ 0.0f, 0.0f });
            ImVec2 displaySize = ImGui::GetIO().DisplaySize;
            ImGui::SetWindowSize({ static_cast<float>(displaySize.x), static_cast<float>(displaySize.y) });
            ImGui::End();

            ImGui::PopStyleVar(3);
        }

        for (auto& panel : m_panels)
            panel->Draw();

        ImGui::Render();

        return true;
    }
}
