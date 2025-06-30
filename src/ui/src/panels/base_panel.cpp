#include "ui/panels/base_panel.hpp"

namespace Engine::UI::Panels
{
    Panels::BasePanel::BasePanel()
    {
        m_panelId = "##" + std::to_string(m_id++);
    }

    bool Panels::BasePanel::Draw()
    {
        if (m_enabled)
        {
            DrawImpl();
            return true;
        }

        return false;
    }
}
