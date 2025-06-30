#pragma once
#ifndef ENGINE_RENDERER_BUFFERS_VERTEX_ARRAY_HPP_
#define ENGINE_RENDERER_BUFFERS_VERTEX_ARRAY_HPP_

#include "vertex_buffer.hpp"

namespace Engine::Renderer::Buffers
{
    enum class EType
    {
        Byte          = 0x1400,
        UnsignedByte  = 0x1401,
        Short         = 0x1402,
        UnsignedShort = 0x1403,
        Int           = 0x1404,
        UnsignedInt   = 0x1405,
        Float         = 0x1406,
        Double        = 0x140A
    };

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        template<typename T>
        void BindAttribute(uint32_t attribute,
                           VertexBuffer<T>& vertexBuffer,
                           EType type, uint64_t count,
                           uint64_t stride, intptr_t offset);

        void Bind();
        void Unbind();

        GLuint GetId();

    private:
        GLuint m_bufferId = 0;
    };
}

#include "renderer/buffers/vertex_array.inl"

#endif // ENGINE_RENDERER_BUFFERS_VERTEX_ARRAY_HPP_
