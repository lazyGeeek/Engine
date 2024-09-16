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

        Tools::Eventing::Event<> ClickedEvent;

    protected:
        virtual void DrawImpl() override = 0;
    };
}

#endif // ENGINE_UI_WIDGETS_BUTTONS_BASE_BUTTON_HPP_
