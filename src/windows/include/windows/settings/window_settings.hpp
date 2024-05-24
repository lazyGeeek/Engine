#pragma once
#ifndef ENGINE_WINDOWS_SETTINGS_WINDOW_SETTINGS_HPP_
#define ENGINE_WINDOWS_SETTINGS_WINDOW_SETTINGS_HPP_

#include <string>

#include <glm/glm.hpp>

#include "windows/settings/sdl2_window_flags.hpp"

namespace Engine::Windows::Settings
{
    struct WindowSettings
    {
        static const int32_t DONT_CARE = -1;

        std::string Title = "Engine";

        glm::i32vec2 Size = glm::i32vec2(1280, 720);
        glm::i32vec2 MinimumSize = glm::i32vec2(DONT_CARE);
        glm::i32vec2 MaximumSize = glm::i32vec2(DONT_CARE);

        ESDL2WindowFlags Flags = ESDL2WindowFlags::None;
        uint32_t Samples = 4;
    };
}

#endif // ENGINE_WINDOWS_SETTINGS_WINDOW_SETTINGS_HPP_
