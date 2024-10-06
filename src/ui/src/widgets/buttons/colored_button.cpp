#include "ui/widgets/buttons/colored_button.hpp"

namespace Engine::UI::Widgets::Buttons
{
    ColoredButton::ColoredButton(const std::string& label, const Types::Color& color, const glm::vec2 size, bool enableAlpha)
        : BaseButton(label),
          m_color { color },
          m_size { Internal::Converter::ToImVec2(size) },
          m_isAlphaEnabled { enableAlpha }
    {
        ImGuiStyle& style = ImGui::GetStyle();

        m_textColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_Text]);
    }

    void ColoredButton::DrawImpl()
    {
        if (!m_enabled)
            return;

        ImGuiStyle& style = ImGui::GetStyle();

        ImVec4 defaultTextColor = style.Colors[ImGuiCol_Text];

        style.Colors[ImGuiCol_Text] = Internal::Converter::ToImVec4(m_textColor);

        if (ImGui::ColorButton((m_label + m_widgetId).c_str(), Internal::Converter::ToImVec4(m_color),
            !m_isAlphaEnabled ? ImGuiColorEditFlags_NoAlpha : 0, m_size))
            ClickedEvent.Invoke();

        style.Colors[ImGuiCol_Text] = defaultTextColor;
    }
}
