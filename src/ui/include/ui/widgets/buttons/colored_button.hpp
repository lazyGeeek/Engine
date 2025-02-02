#pragma once
#ifndef ENGINE_UI_WIDGETS_BUTTONS_COLORED_BUTTON_HPP_
#define ENGINE_UI_WIDGETS_BUTTONS_COLORED_BUTTON_HPP_

#include <glm/glm.hpp>

#include <imgui/imgui.h>

#include "ui/internal/converter.hpp"
#include "ui/types/color.hpp"
#include "ui/widgets/buttons/base_button.hpp"

namespace Engine::UI::Widgets::Buttons
{
    class ColoredButton : public BaseButton
    {
    public:
        ColoredButton(const std::string& label = "",
            const Types::Color& color = Types::Color::Black,
            const glm::vec2 size = glm::vec2(1.0f),
            bool enableAlpha = true);

        virtual ~ColoredButton() = default;

        ColoredButton(const ColoredButton& other)             = delete;
        ColoredButton(ColoredButton&& other)                  = delete;
        ColoredButton& operator=(const ColoredButton& other)  = delete;
        ColoredButton& operator=(const ColoredButton&& other) = delete;

        const Types::Color& GetColor() const { return m_color; }
        const glm::vec2& GetSize()     const { return Internal::Converter::ToGlmVec2(m_size); }

        bool IsAlphaEnabled() const { return m_isAlphaEnabled; }

        void SetColor(const Types::Color& color) { m_color = color; }
        void SetSize(const glm::vec2& size)      { m_size  = Internal::Converter::ToImVec2(size); }

        bool EnableAlpha(bool enableAlpha) { m_isAlphaEnabled = enableAlpha; }

    protected:
        virtual void DrawImpl() override;

    private:
        const Types::Color& GetIdleBackgroundColor()    const override { return m_idleBackgroundColor; }
        const Types::Color& GetHoveredBackgroundColor() const override { return m_hoveredBackgroundColor; }
        const Types::Color& GetClickedBackgroundColor() const override { return m_clickedBackgroundColor; }

        void SetIdleBackgroundColor(const Types::Color& color)    override { }
        void SetHoveredBackgroundColor(const Types::Color& color) override { }
        void SetClickedBackgroundColor(const Types::Color& color) override { }

        Types::Color m_idleBackgroundColor    = Types::Color::Black;
        Types::Color m_hoveredBackgroundColor = Types::Color::Black;
        Types::Color m_clickedBackgroundColor = Types::Color::Black;

        Types::Color m_color  = Types::Color::Black;
        ImVec2 m_size         = ImVec2(1.0f, 1.0f);
        bool m_isAlphaEnabled = true;
    };
}

#endif // ENGINE_UI_WIDGETS_BUTTONS_COLORED_BUTTON_HPP_
