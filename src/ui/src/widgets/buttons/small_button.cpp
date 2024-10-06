#include "ui/widgets/buttons/small_button.hpp"

#include "ui/internal/converter.hpp"

namespace Engine::UI::Widgets::Buttons
{
    SmallButton::SmallButton(const std::string& label)
        : BaseButton(label)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        m_idleBackgroundColor    = Internal::Converter::ToColor(style.Colors[ImGuiCol_Button]);
        m_hoveredBackgroundColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonHovered]);
        m_clickedBackgroundColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonActive]);
        m_textColor              = Internal::Converter::ToColor(style.Colors[ImGuiCol_Text]);
    }

    void SmallButton::DrawImpl()
    {
        if (!m_enabled)
            return;

        ImGuiStyle& style = ImGui::GetStyle();

        ImVec4 defaultIdleColor    = style.Colors[ImGuiCol_Button];
        ImVec4 defaultHoveredColor = style.Colors[ImGuiCol_ButtonHovered];
        ImVec4 defaultClickedColor = style.Colors[ImGuiCol_ButtonActive];
        ImVec4 defaultTextColor    = style.Colors[ImGuiCol_Text];

        style.Colors[ImGuiCol_Button]        = Internal::Converter::ToImVec4(m_idleBackgroundColor);
        style.Colors[ImGuiCol_ButtonHovered] = Internal::Converter::ToImVec4(m_hoveredBackgroundColor);
        style.Colors[ImGuiCol_ButtonActive]  = Internal::Converter::ToImVec4(m_clickedBackgroundColor);
        style.Colors[ImGuiCol_Text]          = Internal::Converter::ToImVec4(m_textColor);

        if (ImGui::SmallButton((m_label + m_widgetId).c_str()))
            ClickedEvent.Invoke();

        style.Colors[ImGuiCol_Button]        = defaultIdleColor;
        style.Colors[ImGuiCol_ButtonHovered] = defaultHoveredColor;
        style.Colors[ImGuiCol_ButtonActive]  = defaultClickedColor;
        style.Colors[ImGuiCol_Text]          = defaultTextColor;
    }
}
