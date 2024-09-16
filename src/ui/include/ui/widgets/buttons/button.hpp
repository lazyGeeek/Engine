#pragma once
#ifndef ENGINE_UI_WIDGETS_BUTTONS_BUTTON_HPP_
#define ENGINE_UI_WIDGETS_BUTTONS_BUTTON_HPP_

#include <string>

#include <imgui/imgui.h>

#include <glm/glm.hpp>

#include "ui/internal/converter.hpp"
#include "ui/widgets/buttons/base_button.hpp"

namespace Engine::UI::Widgets::Buttons
{
    class Button : public BaseButton
    {
    public:
        Button(const std::string& label = "", const glm::vec2& size = glm::vec2(0.0f), bool enabled = true);
        virtual ~Button() = default;

        Button(const Button& other)             = delete;
        Button(Button&& other)                  = delete;
        Button& operator=(const Button& other)  = delete;
        Button& operator=(const Button&& other) = delete;

        //bool IsEnabled()              const { return m_enabled; }
        const std::string& GetLabel() const { return m_label; }
        const glm::vec2& GetSize()    const { return Internal::Converter::ToGlmVec2(m_size); }
        const std::string& GetText()  const { return m_label; }

        const Types::Color& GetIdleBackgroundColor()    const { return m_idleBackgroundColor; }
        const Types::Color& GetHoveredBackgroundColor() const { return m_hoveredBackgroundColor; }
        const Types::Color& GetClickedBackgroundColor() const { return m_clickedBackgroundColor; }
        const Types::Color& GetTextColor()              const { return m_textColor; }

        //void SetEnable(bool value)          { m_enabled = value; }
        void SetSize(const glm::vec2& size)   { m_size = Internal::Converter::ToImVec2(size); }
        void SetText(const std::string& text) { m_label = text; }

        void SetIdleBackgroundColor(const Types::Color& color)    { m_idleBackgroundColor    = color; }
        void SetHoveredBackgroundColor(const Types::Color& color) { m_hoveredBackgroundColor = color; }
        void SetClickedBackgroundColor(const Types::Color& color) { m_clickedBackgroundColor = color; }
        void SetTextColor(const Types::Color& color)              { m_textColor              = color; }

    protected:
        virtual void DrawImpl() override;

        Types::Color m_idleBackgroundColor    = Types::Color::Black;
        Types::Color m_hoveredBackgroundColor = Types::Color::Black;
        Types::Color m_clickedBackgroundColor = Types::Color::Black;
        Types::Color m_textColor              = Types::Color::Black;

        std::string m_label = "";
        ImVec2 m_size       = ImVec2(0.0f, 0.0f);
        //bool m_enabled      = true;
    };
}

#endif // ENGINE_UI_WIDGETS_BUTTONS_BUTTON_HPP_
