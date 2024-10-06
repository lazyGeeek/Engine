#include "ui/widgets/base_widget.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets
{
    BaseWidget::BaseWidget(const std::string& label)
        : m_label { label }
    {
        m_widgetId = "##" + std::to_string(m_id++);
    }

    bool BaseWidget::Draw()
    {
        if (m_enabled)
        {
            DrawImpl();

            if (m_sameLine)
                ImGui::SameLine();

            return true;
        }

        return false;
    }
}
