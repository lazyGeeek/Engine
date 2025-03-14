#pragma once
#ifndef ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP_
#define ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP_

#include <vector>

namespace Engine::Renderer::Buffers
{
    template<typename T>
    class VertexBuffer
    {
    public:
        VertexBuffer(T* data, size_t elements);
        VertexBuffer(std::vector<T>& data);

        ~VertexBuffer();

        void Bind();
        void Unbind();

        uint32_t GetId();

    private:
        uint32_t m_bufferId = 0;
    };
}

#include "renderer/buffers/vertex_buffer.inl"

#endif // ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_HPP_
