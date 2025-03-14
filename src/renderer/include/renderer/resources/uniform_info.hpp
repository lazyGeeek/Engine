#pragma once
#ifndef ENGINE_RENDERER_RESOURCES_UNIFORM_INFO_HPP_
#define ENGINE_RENDERER_RESOURCES_UNIFORM_INFO_HPP_

#include <string>
#include <any>

#include "renderer/resources/uniform_type.hpp"

namespace Engine::Renderer::Resources
{
    struct UniformInfo
    {
        UniformType Type;
        std::string Name;
        uint32_t    Location;
        std::any    DefaultValue;
    };
}

#endif // ENGINE_RENDERER_RESOURCES_UNIFORM_INFO_HPP_
