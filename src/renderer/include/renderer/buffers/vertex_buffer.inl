#pragma once
#ifndef ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_INL_
#define ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_INL_

#include "renderer/buffers/vertex_buffer.hpp"

#include <GL/glew.h>

namespace Engine::Renderer::Buffers
{
    template <class T>
    inline VertexBuffer<T>::VertexBuffer(T* data, size_t elements)
    {
        glGenBuffers(1, &m_bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
        glBufferData(GL_ARRAY_BUFFER, elements * sizeof(T), data, GL_STATIC_DRAW);
    }

    template<class T>
    inline VertexBuffer<T>::VertexBuffer(std::vector<T>& data) :
        VertexBuffer(data.data(), data.size()) { }

    template<class T>
    inline VertexBuffer<T>::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_bufferId);
    }

    template <class T>
    inline void VertexBuffer<T>::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    }

    template <class T>
    inline void VertexBuffer<T>::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    template <class T>
    inline uint32_t VertexBuffer<T>::GetId()
    {
        return m_bufferId;
    }
}

#endif // ENGINE_RENDERER_BUFFERS_VERTEX_BUFFER_INL_
