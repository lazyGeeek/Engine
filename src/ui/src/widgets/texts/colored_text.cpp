#include "ui/widgets/texts/colored_text.hpp"
#include "ui/internal/converter.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Texts
{
    ColoredText::ColoredText(const std::string& content, const Types::Color& color)
        : Text(content), m_color { color }  { }

    void ColoredText::DrawImpl()
    {
        if (!m_enabled)
            return;

        ImGui::TextColored(Internal::Converter::ToImVec4(m_color), m_content.c_str());
    }
}
