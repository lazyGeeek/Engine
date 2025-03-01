#pragma once
#ifndef ENGINE_UI_WIDGETS_TEXTS_TEXT_FILTER_HPP_
#define ENGINE_UI_WIDGETS_TEXTS_TEXT_FILTER_HPP_

#include "ui/widgets/base_widget.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Texts
{
    class TextFilter : public BaseWidget
    {
    public:
        TextFilter(const std::string& label = "") : BaseWidget(label) { }
        virtual ~TextFilter() override = default;

        TextFilter(const TextFilter& other)             = delete;
        TextFilter(TextFilter&& other)                  = delete;
        TextFilter& operator=(const TextFilter& other)  = delete;
        TextFilter& operator=(const TextFilter&& other) = delete;

        virtual bool PassFilter(const std::string& line) { return m_filter.PassFilter(line.c_str()); }

        virtual std::string GetFilterText() { return std::string(m_filter.InputBuf); }

    protected:
        virtual void DrawImpl() override
        {
            if (m_label.empty())
                m_filter.Draw();
            else
                m_filter.Draw(m_label.c_str());
        }

        ImGuiTextFilter m_filter;

    };
}

#endif // ENGINE_UI_WIDGETS_TEXTS_TEXT_FILTER_HPP_
