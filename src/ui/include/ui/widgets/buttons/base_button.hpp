#pragma once
#ifndef ENGINE_UI_WIDGETS_BUTTONS_BASE_BUTTON_HPP_
#define ENGINE_UI_WIDGETS_BUTTONS_BASE_BUTTON_HPP_

#include "tools/eventing/event.hpp"
#include "ui/widgets/base_widget.hpp"

namespace Engine::UI::Widgets::Buttons
{
    class BaseButton : public BaseWidget
    {
    public:
        BaseButton()          = default;
        virtual ~BaseButton() = default;

        BaseButton(const BaseButton& other)             = delete;
        BaseButton(BaseButton&& other)                  = delete;
        BaseButton& operator=(const BaseButton& other)  = delete;
        BaseButton& operator=(const BaseButton&& other) = delete;

        virtual const Types::Color& GetIdleBackgroundColor()    const { return m_idleBackgroundColor; }
        virtual const Types::Color& GetHoveredBackgroundColor() const { return m_hoveredBackgroundColor; }
        virtual const Types::Color& GetClickedBackgroundColor() const { return m_clickedBackgroundColor; }
        virtual const Types::Color& GetTextColor()              const { return m_textColor; }

        virtual const std::string& GetText() const { return m_label; }

        virtual void SetIdleBackgroundColor(const Types::Color& color)    { m_idleBackgroundColor    = color; }
        virtual void SetHoveredBackgroundColor(const Types::Color& color) { m_hoveredBackgroundColor = color; }
        virtual void SetClickedBackgroundColor(const Types::Color& color) { m_clickedBackgroundColor = color; }
        virtual void SetTextColor(const Types::Color& color)              { m_textColor              = color; }

        virtual void SetText(const std::string& text) { m_label = text; }

        Tools::Eventing::Event<> ClickedEvent;

    protected:
        virtual void DrawImpl() override = 0;

        Types::Color m_idleBackgroundColor    = Types::Color::Black;
        Types::Color m_hoveredBackgroundColor = Types::Color::Black;
        Types::Color m_clickedBackgroundColor = Types::Color::Black;
        Types::Color m_textColor              = Types::Color::Black;

        std::string m_label = "";
    };
}

#endif // ENGINE_UI_WIDGETS_BUTTONS_BASE_BUTTON_HPP_
