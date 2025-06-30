#pragma once
#ifndef ENGINE_RENDERER_SETTINGS_RASTERIZATION_MODE_HPP_
#define ENGINE_RENDERER_SETTINGS_RASTERIZATION_MODE_HPP_

namespace Engine::Renderer::Settings
{
    enum class ERasterizationMode
    {
        Point = 0x1B00,
        Line  = 0x1B01,
        Fill  = 0x1B02 
    };
}

#endif // ENGINE_RENDERER_SETTINGS_RASTERIZATION_MODE_HPP_
