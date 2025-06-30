#include "ui/widgets/buttons/arrow_button.hpp"

#include "ui/internal/converter.hpp"

namespace Engine::UI::Widgets::Buttons
{
    ArrowButton::ArrowButton(EDirection direction)
        : BaseButton(""), m_direction { fromEDirection(direction) }
    {
        ImGuiStyle& style = ImGui::GetStyle();

        m_backgroundColor        = Internal::Converter::ToColor(style.Colors[ImGuiCol_Button]);
        m_hoveredBackgroundColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonHovered]);
        m_activeBackgroundColor  = Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonActive]);
        m_textColor              = Internal::Converter::ToColor(style.Colors[ImGuiCol_Text]);
    }

    void ArrowButton::DrawImpl()
    {
        if (!m_enabled)
            return;

        ImGuiStyle& style = ImGui::GetStyle();

        ImVec4 defaultColor        = style.Colors[ImGuiCol_Button];
        ImVec4 defaultHoveredColor = style.Colors[ImGuiCol_ButtonHovered];
        ImVec4 defaultActiveColor  = style.Colors[ImGuiCol_ButtonActive];
        ImVec4 defaultTextColor    = style.Colors[ImGuiCol_Text];

        style.Colors[ImGuiCol_Button]        = Internal::Converter::ToImVec4(m_backgroundColor);
        style.Colors[ImGuiCol_ButtonHovered] = Internal::Converter::ToImVec4(m_hoveredBackgroundColor);
        style.Colors[ImGuiCol_ButtonActive]  = Internal::Converter::ToImVec4(m_activeBackgroundColor);
        style.Colors[ImGuiCol_Text]          = Internal::Converter::ToImVec4(m_textColor);

        if (ImGui::ArrowButton(m_widgetId.c_str(), m_direction))
            ClickedEvent.Invoke();

        style.Colors[ImGuiCol_Button]        = defaultColor;
        style.Colors[ImGuiCol_ButtonHovered] = defaultHoveredColor;
        style.Colors[ImGuiCol_ButtonActive]  = defaultActiveColor;
        style.Colors[ImGuiCol_Text]          = defaultTextColor;
    }

    ArrowButton::EDirection ArrowButton::fromImGuiDir(ImGuiDir direction)
    {
        switch (direction)
        {
            case ImGuiDir_Right:
                return EDirection::Right;
            case ImGuiDir_Up:
                return EDirection::Up;
            case ImGuiDir_Down:
                return EDirection::Down;
            case ImGuiDir_Left:
            default:
                return EDirection::Left;
        }
    }

    ImGuiDir ArrowButton::fromEDirection(EDirection direction)
    {
        switch (direction)
        {
            case EDirection::Right:
                return ImGuiDir_Right;
            case EDirection::Up:
                return ImGuiDir_Up;
            case EDirection::Down:
                return ImGuiDir_Down;
            case EDirection::Left:
            default:
                return ImGuiDir_Left;
        }
    }
}
