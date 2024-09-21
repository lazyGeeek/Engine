#pragma once
#ifndef ENGINE_UI_WIDGETS_BUTTONS_ARROW_BUTTON_HPP_
#define ENGINE_UI_WIDGETS_BUTTONS_ARROW_BUTTON_HPP_

#include <imgui/imgui.h>

#include "ui/types/color.hpp"
#include "ui/widgets/buttons/base_button.hpp"

namespace Engine::UI::Widgets::Buttons
{
    class ArrowButton : public BaseButton
    {
    public:
        enum class EDirection
        {
            Left = 0,
            Right = 1,
            Up = 2,
            Down = 3
        };

        ArrowButton(EDirection direction = EDirection::Left, bool enabled = true);
        virtual ~ArrowButton() = default;

        ArrowButton(const ArrowButton& other)             = delete;
        ArrowButton(ArrowButton&& other)                  = delete;
        ArrowButton& operator=(const ArrowButton& other)  = delete;
        ArrowButton& operator=(const ArrowButton&& other) = delete;

        EDirection GetDirection() { return fromImGuiDir(m_direction); }

        void SetDirection(EDirection direction) { m_direction = fromEDirection(direction); }

    protected:
        virtual void DrawImpl() override;

        EDirection fromImGuiDir(ImGuiDir direction);
        ImGuiDir fromEDirection(EDirection direction);

    private:
        const std::string& GetText() const override { return m_label; }
        void SetText(const std::string& text) override { }

        ImGuiDir m_direction = ImGuiDir_Left;

        std::string m_label = "";
    };
}

#endif // ENGINE_UI_WIDGETS_BUTTONS_ARROW_BUTTON_HPP_
