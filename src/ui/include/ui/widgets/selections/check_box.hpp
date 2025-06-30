#pragma once
#ifndef ENGINE_UI_WIDGETS_SELECTIONS_CHECK_BOX_HPP_
#define ENGINE_UI_WIDGETS_SELECTIONS_CHECK_BOX_HPP_

#include "ui/widgets/base_widget.hpp"
#include "tools/eventing/event.hpp"

namespace Engine::UI::Widgets::Selections
{
    class CheckBox : public BaseWidget
    {
    public:
        CheckBox(const std::string& label, bool value = false);
        virtual ~CheckBox() = default;

        CheckBox(const CheckBox& other)             = delete;
        CheckBox(CheckBox&& other)                  = delete;
        CheckBox& operator=(const CheckBox& other)  = delete;
        CheckBox& operator=(const CheckBox&& other) = delete;

        bool GetValue() const { return m_value; }
        void SetValue(bool value);

        Tools::Eventing::Event<bool> ValueChangedEvent;

    protected:
        virtual void DrawImpl() override;

        bool m_value = false;
    };
}

#endif // ENGINE_UI_WIDGETS_SELECTIONS_CHECK_BOX_HPP_
