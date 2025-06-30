#pragma once
#ifndef ENGINE_UI_INTERNAL_CONVERTER_HPP_
#define ENGINE_UI_INTERNAL_CONVERTER_HPP_

#include <imgui/imgui.h>

#include <glm/glm.hpp>

#include "ui/types/color.hpp"

namespace Engine::UI::Internal
{
    struct Converter
    {
    public:
        static ImVec2 ToImVec2(const glm::vec2& vec2)
        {
            return ImVec2(vec2.x, vec2.y);
        }

        static ImVec4 ToImVec4(const Types::Color& color)
        {
            return ImVec4(color.R, color.G, color.B, color.A);
        }

        static Types::Color ToColor(const ImVec4& imVec2)
        {
            return Types::Color(imVec2.x, imVec2.y, imVec2.z, imVec2.w);
        }

        static glm::vec2 ToGlmVec2(const ImVec2& imVec2)
        {
            return glm::vec2(imVec2.x, imVec2.y);
        }
    };
}

#endif // ENGINE_UI_INTERNAL_CONVERTER_HPP_
