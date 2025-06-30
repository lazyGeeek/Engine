#pragma once
#ifndef ENGINE_UI_WIDGETS_PLOTS_PLOT_LINES_HPP_
#define ENGINE_UI_WIDGETS_PLOTS_PLOT_LINES_HPP_

#include <vector>

#include <imgui/imgui.h>

#include <glm/glm.hpp>

#include "ui/widgets/plots/base_plot.hpp"

namespace Engine::UI::Widgets::Plots
{
    class PlotLines : public BasePlot
    {
    public:
        PlotLines(const std::string& label,
            const std::string& overlay = "",
            unsigned samplesToShow = 50,
            float minScale = std::numeric_limits<float>::min(),
            float maxScale = std::numeric_limits<float>::max(),
            const glm::vec2& size = glm::vec2(0.0f));

        virtual ~PlotLines() = default;

        PlotLines(const PlotLines& other)             = delete;
        PlotLines(PlotLines&& other)                  = delete;
        PlotLines& operator=(const PlotLines& other)  = delete;
        PlotLines& operator=(const PlotLines&& other) = delete;

    protected:
        virtual void DrawImpl() override;
    };
}

#endif // ENGINE_UI_WIDGETS_PLOTS_PLOT_LINES_HPP_
