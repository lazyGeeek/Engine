#pragma once
#ifndef ENGINE_RENDERER_BUFFERS_VERTEX_ARRAY_INL_
#define ENGINE_RENDERER_BUFFERS_VERTEX_ARRAY_INL_

#include "renderer/buffers/vertex_array.hpp"

namespace Engine::Renderer::Buffers
{
    template <class T>
    inline void VertexArray::BindAttribute(uint32_t attribute, VertexBuffer<T>& vertexBuffer,
                                           EType type, uint64_t count,
                                           uint64_t stride, intptr_t offset)
    {
        Bind();
        vertexBuffer.Bind();
        glEnableVertexAttribArray(attribute);
        glVertexAttribPointer(static_cast<GLuint>(attribute),
                              static_cast<GLint>(count),
                              static_cast<GLenum>(type), GL_FALSE,
                              static_cast<GLsizei>(stride),
                              reinterpret_cast<const GLvoid*>(offset));
    }
}

#endif // ENGINE_RENDERER_BUFFERS_VERTEX_ARRAY_INL_
