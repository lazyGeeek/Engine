#include "renderer/buffers/index_buffer.hpp"

#include <GL/glew.h>

namespace Engine::Renderer::Buffers
{
    Buffers::IndexBuffer::IndexBuffer(unsigned int* data, size_t elements)
    {
        glGenBuffers(1, &m_bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    Buffers::IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_bufferId);
    }

    void Buffers::IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    }

    void Buffers::IndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t Buffers::IndexBuffer::GetId()
    {
        return m_bufferId;
    }
}
