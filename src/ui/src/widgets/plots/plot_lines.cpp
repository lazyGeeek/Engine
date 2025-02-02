#include "ui/widgets/plots/plot_lines.hpp"
#include "ui/internal/converter.hpp"

namespace Engine::UI::Widgets::Plots
{
    PlotLines::PlotLines(const std::string& label,
        const std::string& overlay,
        unsigned samplesToShow,
        float minScale, float maxScale,
        const glm::vec2& size)
        : BasePlot(label, overlay, samplesToShow, minScale, maxScale, size) { }

    void PlotLines::DrawImpl()
    {
        ImGui::PlotLines((m_label + m_widgetId).c_str(), m_data.data(),
            static_cast<int>(m_data.size()),
            0, m_overlay.c_str(), m_minScale, m_maxScale,
            m_size, sizeof(float));
    }
}
