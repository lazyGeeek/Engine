#pragma once
#ifndef ENGINE_UI_WIDGETS_PLOTS_BASE_PLOT_HPP_
#define ENGINE_UI_WIDGETS_PLOTS_BASE_PLOT_HPP_

#include <vector>

#include <imgui/imgui.h>

#include <glm/glm.hpp>

#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Plots
{
    class BasePlot : public BaseWidget
    {
    public:
        BasePlot(const std::string& label,
            const std::string& overlay = "",
            unsigned samplesToShow = 50,
            float minScale = std::numeric_limits<float>::min(),
            float maxScale = std::numeric_limits<float>::max(),
            const glm::vec2& size = glm::vec2(0.0f));

        virtual ~BasePlot() = default;

        BasePlot(const BasePlot& other)             = delete;
        BasePlot(BasePlot&& other)                  = delete;
        BasePlot& operator=(const BasePlot& other)  = delete;
        BasePlot& operator=(const BasePlot&& other) = delete;

        virtual void SetOverlay(const std::string& overlay)  { m_overlay    = overlay; }
        virtual void SetMinScale(float minScale)             { m_minScale   = minScale; }
        virtual void SetMaxScale(float maxScale)             { m_maxScale   = maxScale; }

        virtual void SetSize(const glm::vec2& size);
        virtual void SetData(const std::initializer_list<float>& data);
        virtual void SetSamplesToShow(unsigned samplesToShow);
        virtual void AddSample(float sample);

        virtual const std::string& GetOverlay()     const { return m_overlay; }
        virtual const std::vector<float>& GetData() const { return m_data; }
        virtual float GetMinScale()                 const { return m_minScale; }
        virtual float GetMaxScale()                 const { return m_maxScale; }
        virtual unsigned GetSamplesToShowCount()    const { return static_cast<unsigned>(m_data.size()); }
        virtual const glm::vec2 GetSize()           const;

    protected:
        virtual void DrawImpl() override = 0;

        std::string m_overlay     = "";
        std::vector<float> m_data = std::vector<float>();
        unsigned m_samplesToShow  = 50;
        float m_minScale          = std::numeric_limits<float>::min();
        float m_maxScale          = std::numeric_limits<float>::max();
        ImVec2 m_size             = ImVec2(1.0f, 1.0f);
    };
}

#endif // ENGINE_UI_WIDGETS_PLOTS_BASE_PLOT_HPP_
