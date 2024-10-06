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
        Button(const std::string& label = "", const glm::vec2& size = glm::vec2(0.0f));
        virtual ~Button() = default;

        Button(const Button& other)             = delete;
        Button(Button&& other)                  = delete;
        Button& operator=(const Button& other)  = delete;
        Button& operator=(const Button&& other) = delete;

        const glm::vec2& GetSize() const { return Internal::Converter::ToGlmVec2(m_size); }

        void SetSize(const glm::vec2& size) { m_size = Internal::Converter::ToImVec2(size); }

    protected:
        virtual void DrawImpl() override;

        ImVec2 m_size = ImVec2(0.0f, 0.0f);
    };
}

#endif // ENGINE_UI_WIDGETS_BUTTONS_BUTTON_HPP_
