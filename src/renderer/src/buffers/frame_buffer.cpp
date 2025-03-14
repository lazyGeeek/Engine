#include "renderer/buffers/frame_buffer.hpp"

#include <GL/glew.h>

namespace Engine::Renderer::Buffers
{
    FrameBuffer::FrameBuffer(uint16_t width, uint16_t height)
    {
        glGenFramebuffers(1, &m_bufferId);
        glGenTextures(1, &m_renderTextureId);
        glGenRenderbuffers(1, &m_depthStencilBufferId);

        glBindTexture(GL_TEXTURE_2D, m_renderTextureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        Bind();
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderTextureId, 0);
        Unbind();

        Resize(width, height);
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteBuffers(1, &m_bufferId);
        glDeleteTextures(1, &m_renderTextureId);
        glDeleteRenderbuffers(1, &m_depthStencilBufferId);
    }

    void FrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_bufferId);
    }

    void FrameBuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::Resize(uint16_t width, uint16_t height)
    {
        glBindTexture(GL_TEXTURE_2D, m_renderTextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, m_depthStencilBufferId);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        Bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBufferId);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStencilBufferId);
        Unbind();
    }

    uint32_t FrameBuffer::GetRenderTextureId() const
    {
        return m_renderTextureId;
    }
}
