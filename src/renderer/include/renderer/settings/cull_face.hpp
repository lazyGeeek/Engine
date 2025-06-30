#pragma once
#ifndef ENGINE_RENDERER_SETTINGS_CULL_FACE_HPP_
#define ENGINE_RENDERER_SETTINGS_CULL_FACE_HPP_

namespace Engine::Renderer::Settings
{
    enum class ECullFace
    {
        Front        = 0x0404,
        Back         = 0x0405,
        FrontAndBack = 0x0408
    };
}

#endif // ENGINE_RENDERER_SETTINGS_CULL_FACE_HPP_
