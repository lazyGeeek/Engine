#pragma once
#ifndef ENGINE_UI_WIDGETS_INTERFACES_RESIZABLE_HPP_
#define ENGINE_UI_WIDGETS_INTERFACES_RESIZABLE_HPP_

#include <glm/glm.hpp>

namespace Engine::UI::Widgets::Interfaces
{
    class Resizable
    {
    public:
        virtual void Resize(const glm::vec2& size) { m_size = size; }
        virtual const glm::vec2& GetSize() const { return m_size; }

    protected:
        glm::vec2 m_size = glm::vec2(1.0f, 1.0f);
    };
}

#endif // ENGINE_UI_WIDGETS_INTERFACES_RESIZABLE_HPP_
