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
        BaseButton(const std::string& label) : BaseWidget(label) { }

        virtual ~BaseButton() = default;

        BaseButton(const BaseButton& other)             = delete;
        BaseButton(BaseButton&& other)                  = delete;
        BaseButton& operator=(const BaseButton& other)  = delete;
        BaseButton& operator=(const BaseButton&& other) = delete;

        virtual const Types::Color& GetBackgroundColor()        const { return m_backgroundColor; }
        virtual const Types::Color& GetHoveredBackgroundColor() const { return m_hoveredBackgroundColor; }
        virtual const Types::Color& GetActiveBackgroundColor()  const { return m_activeBackgroundColor; }
        virtual const Types::Color& GetTextColor()              const { return m_textColor; }

        virtual void SetBackgroundColor(const Types::Color& color)        { m_backgroundColor        = color; }
        virtual void SetHoveredBackgroundColor(const Types::Color& color) { m_hoveredBackgroundColor = color; }
        virtual void SetActiveBackgroundColor(const Types::Color& color)  { m_activeBackgroundColor  = color; }
        virtual void SetTextColor(const Types::Color& color)              { m_textColor              = color; }

        Tools::Eventing::Event<> ClickedEvent;

    protected:
        virtual void DrawImpl() override = 0;

        Types::Color m_backgroundColor        = Types::Color::Black;
        Types::Color m_hoveredBackgroundColor = Types::Color::Black;
        Types::Color m_activeBackgroundColor  = Types::Color::Black;
        Types::Color m_textColor              = Types::Color::Black;
    };
}

#endif // ENGINE_UI_WIDGETS_BUTTONS_BASE_BUTTON_HPP_
