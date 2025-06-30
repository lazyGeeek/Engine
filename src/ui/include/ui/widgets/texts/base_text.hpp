#pragma once
#ifndef ENGINE_UI_WIDGETS_TEXTS_BASE_TEXT_HPP_
#define ENGINE_UI_WIDGETS_TEXTS_BASE_TEXT_HPP_

#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Texts
{
    class BaseText : public BaseWidget
    {
    public:
        BaseText(const std::string& label, const std::string& content)
            : BaseWidget(label), m_content { content } { }
        virtual ~BaseText() override = default;

        BaseText(const BaseText& other)             = delete;
        BaseText(BaseText&& other)                  = delete;
        BaseText& operator=(const BaseText& other)  = delete;
        BaseText& operator=(const BaseText&& other) = delete;

        virtual const std::string& GetContent() const { return m_content; }
        virtual void SetContent(const std::string& content) { m_content = content; }

    protected:
        virtual void DrawImpl() override = 0;

        std::string m_content = "";

    };
}

#endif // ENGINE_UI_WIDGETS_TEXTS_BASE_TEXT_HPP_
