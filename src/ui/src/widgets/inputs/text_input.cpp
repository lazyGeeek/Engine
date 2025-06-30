#include "ui/widgets/inputs/text_input.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Inputs
{
    TextInput::TextInput(const std::string& label, const std::string& content,
        const std::string& hint, bool selectAllOnClick)
        : BaseWidget(label), m_content{ content }, m_hint { hint },
          m_selectAllOnClick{ selectAllOnClick } { }

    TextInput::~TextInput()
    {
        ContentChangedEvent.RemoveAllListeners();
        EnterPressedEvent.RemoveAllListeners();
    }

    void TextInput::DrawImpl()
    {
        if (!m_enabled)
            return;

        std::string previousContent = m_content;

        m_content.resize(CONTENT_BUFFER_SIZE, '\0');

        bool enterPressed = ImGui::InputTextWithHint((m_label + m_widgetId).c_str(), m_hint.data(), m_content.data(),
            CONTENT_BUFFER_SIZE, ImGuiInputTextFlags_EnterReturnsTrue |
            (m_selectAllOnClick ? ImGuiInputTextFlags_AutoSelectAll : 0));

        m_content = m_content.c_str();

        if (m_content != previousContent)
            ContentChangedEvent.Invoke(m_content);

        if (enterPressed)
            EnterPressedEvent.Invoke(m_content);
    }
}
