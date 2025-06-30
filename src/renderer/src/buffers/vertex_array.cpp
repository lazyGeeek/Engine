#include "renderer/buffers/vertex_array.hpp"

namespace Engine::Renderer::Buffers
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_bufferId);
        glBindVertexArray(m_bufferId);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_bufferId);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_bufferId);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    GLuint VertexArray::GetId()
    {
        return m_bufferId;
    }
}
