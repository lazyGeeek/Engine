#pragma once
#ifndef ENGINE_RENDERER_BUFFERS_FRAME_BUFFER_HPP_
#define ENGINE_RENDERER_BUFFERS_FRAME_BUFFER_HPP_

#include <stdint.h>

namespace Engine::Renderer::Buffers
{
    class FrameBuffer
    {
    public:

        FrameBuffer(uint16_t width = 0, uint16_t height = 0);
        ~FrameBuffer();

        void Bind();
        void Unbind();

        void Resize(uint16_t width, uint16_t height);

        uint32_t GetRenderTextureId() const;

    private:
        uint32_t m_bufferId             = 0;
        uint32_t m_renderTextureId      = 0;
        uint32_t m_depthStencilBufferId = 0;
    };
}

#endif // ENGINE_RENDERER_BUFFERS_FRAME_BUFFER_HPP_
