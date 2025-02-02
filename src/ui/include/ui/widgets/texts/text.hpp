#pragma once
#ifndef ENGINE_UI_WIDGETS_TEXTS_TEXT_HPP_
#define ENGINE_UI_WIDGETS_TEXTS_TEXT_HPP_

#include "ui/widgets/texts/base_text.hpp"

namespace Engine::UI::Widgets::Texts
{
    class Text : public BaseText
    {
    public:
        Text(const std::string& content);
        virtual ~Text() override = default;

        Text(const Text& other)             = delete;
        Text(Text&& other)                  = delete;
        Text& operator=(const Text& other)  = delete;
        Text& operator=(const Text&& other) = delete;

    protected:
        virtual void DrawImpl() override;

    };
}

#endif // ENGINE_UI_WIDGETS_TEXTS_TEXT_HPP_
