#pragma once
#ifndef ENGINE_UI_WIDGETS_TEXTS_COLORED_TEXT_HPP_
#define ENGINE_UI_WIDGETS_TEXTS_COLORED_TEXT_HPP_

#include "ui/types/color.hpp"
#include "ui/widgets/texts/text.hpp"

namespace Engine::UI::Widgets::Texts
{
    class ColoredText : public Text
    {
    public:
        ColoredText(const std::string& content, const Types::Color& color = Types::Color::Black);
        virtual ~ColoredText() override = default;

        ColoredText(const ColoredText& other)             = delete;
        ColoredText(ColoredText&& other)                  = delete;
        ColoredText& operator=(const ColoredText& other)  = delete;
        ColoredText& operator=(const ColoredText&& other) = delete;

        const Types::Color& GetColor() const { return m_color; }
        void SetColor(const Types::Color& color) { m_color = color; }

    protected:
        virtual void DrawImpl() override;

        Types::Color m_color = Types::Color::Black;;
    };
}

#endif // ENGINE_UI_WIDGETS_TEXTS_COLORED_TEXT_HPP_
