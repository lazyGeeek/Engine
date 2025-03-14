#include "ui/widgets/layouts/group.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Layouts
{
    Group::Group(const Settings::GroupWidgetSettings& groupSettings)
        : BaseWidget("Group"), m_groupSettings { groupSettings } { }

    Group::~Group()
    {
        RemoveAllWidgets();
    }

    void Group::DrawImpl()
    {
        if (!m_enabled)
            return;

        int groupFlags = ImGuiWindowFlags_None;

        if (m_groupSettings.Border)                  groupFlags |= ImGuiChildFlags_Border;
        if (m_groupSettings.AlwaysUseWindowPadding)  groupFlags |= ImGuiChildFlags_AlwaysUseWindowPadding;
        if (m_groupSettings.ResizeX)                 groupFlags |= ImGuiChildFlags_ResizeX;
        if (m_groupSettings.ResizeY)                 groupFlags |= ImGuiChildFlags_ResizeY;
        if (m_groupSettings.AutoResizeX)             groupFlags |= ImGuiChildFlags_AutoResizeX;
        if (m_groupSettings.AutoResizeY)             groupFlags |= ImGuiChildFlags_AutoResizeY;
        if (m_groupSettings.FrameStyle)              groupFlags |= ImGuiChildFlags_FrameStyle;

        if (ImGui::BeginChild((m_label + m_widgetId).c_str(), ImVec2(0.0f, 0.0f), groupFlags))
        {
            if (m_mustScrollToBottom)
            {
                ImGui::SetScrollY(ImGui::GetScrollMaxY());
                m_mustScrollToBottom = false;
            }

            if (m_mustScrollToTop)
            {
                ImGui::SetScrollY(0.0f);
                m_mustScrollToTop = false;
            }

            if (m_mustScrollToRight)
            {
                ImGui::SetScrollX(ImGui::GetScrollMaxX());
                m_mustScrollToRight = false;
            }

            if (m_mustScrollToLeft)
            {
                ImGui::SetScrollX(0.0f);
                m_mustScrollToLeft = false;
            }

            DrawWidgets();
        }

        ImGui::EndChild();
    }
}
