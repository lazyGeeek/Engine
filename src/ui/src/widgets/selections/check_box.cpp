#include "ui/widgets/selections/check_box.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Selections
{
    CheckBox::CheckBox(const std::string& label, bool value)
        : BaseWidget(label), m_value { value } { }

    void CheckBox::SetValue(bool value)
    {
        m_value = value;
        ValueChangedEvent.Invoke(value);
    }

    void CheckBox::DrawImpl()
    {
        bool previousValue = m_value;

        ImGui::Checkbox((m_label + m_widgetId).c_str(), &m_value);

        if (m_value != previousValue)
            ValueChangedEvent.Invoke(m_value);
    }
}
