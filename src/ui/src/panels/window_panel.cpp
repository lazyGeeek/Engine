#include "ui/panels/window_panel.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <iostream>
#include "ui/widgets/buttons/button.hpp"

namespace Engine::UI::Panels
{
    WindowPanel::WindowPanel(const std::string& name, bool opened, const Settings::PanelWindowSettings& windowSettings)
        : m_name { name },
          m_opened { opened },
          m_windowSettings { windowSettings }
    {
        m_autoSize = windowSettings.AutoSize;
    }

    WindowPanel::~WindowPanel()
    {
        RemoveAllWidgets();
    }

    void WindowPanel::Open()
    {
        if (m_opened)
            return;

        m_opened = true;
        OpenEvent.Invoke();
    }

    void WindowPanel::Close()
    {
        if (!m_opened)
            return;

        m_opened = false;
        CloseEvent.Invoke();
    }

    void WindowPanel::Focus()
    {
        ImGui::SetWindowFocus((m_name + m_panelId).c_str());
    }

    void WindowPanel::SetOpened(bool value)
    {
        if (value == m_opened)
            return;

        m_opened = value;

        if (m_opened)
            OpenEvent.Invoke();
        else
            CloseEvent.Invoke();
    }

    bool WindowPanel::IsAppearing() const
    {
        if (ImGuiWindow* window = ImGui::FindWindowByName((m_name + GetPanelId()).c_str()); window)
            return window->Appearing;
        else
            return false;
    }

    void WindowPanel::DrawImpl()
    {
        if (m_opened)
        {
            int windowFlags = ImGuiWindowFlags_None;

            if (!m_windowSettings.Resizable)               windowFlags |= ImGuiWindowFlags_NoResize;
            if (!m_windowSettings.Movable)                 windowFlags |= ImGuiWindowFlags_NoMove;
            if (!m_windowSettings.Dockable)                windowFlags |= ImGuiWindowFlags_NoDocking;
            if (m_windowSettings.HideBackground)           windowFlags |= ImGuiWindowFlags_NoBackground;
            if (m_windowSettings.ForceHorizontalScrollbar) windowFlags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
            if (m_windowSettings.ForceVerticalScrollbar)   windowFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
            if (m_windowSettings.AllowHorizontalScrollbar) windowFlags |= ImGuiWindowFlags_HorizontalScrollbar;
            if (!m_windowSettings.BringToFrontOnFocus)     windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
            if (!m_windowSettings.Collapsable)             windowFlags |= ImGuiWindowFlags_NoCollapse;
            if (!m_windowSettings.AllowInputs)             windowFlags |= ImGuiWindowFlags_NoInputs;
            if (!m_windowSettings.Scrollable)              windowFlags |= ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar;
            if (!m_windowSettings.TitleBar)                windowFlags |= ImGuiWindowFlags_NoTitleBar;

            ImVec2 minSizeConstraint(m_minSize.x, m_minSize.y);
            ImVec2 maxSizeConstraint(m_maxSize.x, m_maxSize.y);

            if (minSizeConstraint.x <= 0.0f || minSizeConstraint.y <= 0.0f)
                minSizeConstraint = { 0.0f, 0.0f };

            if (maxSizeConstraint.x <= 0.0f || maxSizeConstraint.y <= 0.0f)
                maxSizeConstraint = { 100000.0f, 100000.0f };

            ImGui::SetNextWindowSizeConstraints(minSizeConstraint, maxSizeConstraint);

            if (ImGui::Begin((m_name + m_panelId).c_str(), m_windowSettings.Closable ? &m_opened : nullptr, windowFlags))
            {
                m_hovered = ImGui::IsWindowHovered();
                m_focused = ImGui::IsWindowFocused();

                float scrollY = ImGui::GetScrollY();

                m_scrolledToBottom = scrollY == ImGui::GetScrollMaxY();
                m_scrolledToTop = scrollY == 0.0f;

                if (!m_opened)
                    CloseEvent.Invoke();

                Update();

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

            ImGui::End();
        }
    }
}
