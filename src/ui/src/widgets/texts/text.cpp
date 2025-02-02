#include "ui/widgets/texts/text.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Texts
{
    Text::Text(const std::string& content)
        : BaseText("Text", content) { }

    void Text::DrawImpl()
    {
        if (!m_enabled)
            return;

        ImGui::Text(m_content.c_str());
    }
}
