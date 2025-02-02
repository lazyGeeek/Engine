#include "ui/widgets/plots/base_plot.hpp"
#include "ui/internal/converter.hpp"

namespace Engine::UI::Widgets::Plots
{
    BasePlot::BasePlot(const std::string& label,
        const std::string& overlay,
        unsigned samplesToShow,
        float minScale, float maxScale,
        const glm::vec2& size)
        : BaseWidget(label),
          m_overlay { overlay },
          m_minScale { minScale },
          m_maxScale { maxScale },
          m_size { Internal::Converter::ToImVec2(size) }
    {
        m_samplesToShow = samplesToShow == 0 ? 1 : samplesToShow;
        m_data = std::vector<float>(m_samplesToShow, 0.0f);
    }

    void BasePlot::SetSize(const glm::vec2& size)
    {
        m_size = Internal::Converter::ToImVec2(size);
    }

    void BasePlot::SetData(const std::initializer_list<float>& data)
    {
        if (data.size() > m_samplesToShow)
        {
            size_t diff = data.size() - m_samplesToShow;
            m_data.assign(data.begin() + diff, data.end());
            return;
        }

        m_data.assign(data);
    }

    void BasePlot::SetSamplesToShow(unsigned samplesToShow)
    {
        m_samplesToShow = samplesToShow == 0 ? 1 : samplesToShow;
        m_data.resize(m_samplesToShow, 0.0f);
    }

    void BasePlot::AddSample(float sample)
    {
        if (m_data.size() < m_samplesToShow)
        {
            m_data.push_back(sample);
            return;
        }

        std::vector<float> newData(m_data.begin() + 1, m_data.end());
        newData.push_back(sample);
        m_data.swap(newData);
    }

    const glm::vec2 BasePlot::GetSize() const
    {
        return Internal::Converter::ToGlmVec2(m_size);
    }
}
