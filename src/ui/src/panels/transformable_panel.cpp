#include "ui/panels/transformable_panel.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Panels
{
    TransformablePanel::TransformablePanel
    (
        const glm::vec2& position, const glm::vec2& size,
        Settings::EVerticalAlignment defaultVerticalAlignment,
        Settings::EHorizontalAlignment defaultHorizontalAlignment,
        bool ignoreConfigFile
    ) : m_defaultVerticalAlignment   { defaultVerticalAlignment },
        m_defaultHorizontalAlignment { defaultHorizontalAlignment },
        m_ignoreConfigFile           { ignoreConfigFile }
    {
        Resize(m_size);
        SetPosition(m_position);
        SetVerticalAlignment(m_defaultVerticalAlignment);
        SetHorizontalAlignment(m_defaultHorizontalAlignment);
    }

    void TransformablePanel::SetPosition(const glm::vec2& position)
    {
        m_position = position;
        m_positionChanged = true;
    }

    void TransformablePanel::SetHorizontalAlignment(Settings::EHorizontalAlignment horizontalAlignment)
    {
        m_horizontalAlignment = horizontalAlignment;
        m_alignmentChanged = true;
    }

    void TransformablePanel::SetVerticalAlignment(Settings::EVerticalAlignment verticalAligment)
    {
        m_verticalAlignment = verticalAligment;
        m_alignmentChanged = true;
    }

    void TransformablePanel::Resize(const glm::vec2& size)
    {
        m_size = size;
        m_sizeChanged = true;
    }

    glm::vec2 TransformablePanel::GetContentSize() const
    {
        return m_contentSize;
    }

    void TransformablePanel::updatePosition()
    {
        if (m_positionChanged || m_alignmentChanged)
        {
            glm::vec2 offset = calculatePositionAlignmentOffset(false);
            glm::vec2 offsettedPos(m_position.x + offset.x, m_position.y + offset.y);
            ImGui::SetWindowPos(ImVec2(offsettedPos.x, offsettedPos.y), ImGuiCond_Always);
            m_positionChanged = false;
            m_alignmentChanged = false;
        }
    }

    void TransformablePanel::updateSize()
    {
        if (m_sizeChanged)
        {
            ImGui::SetWindowSize(ImVec2(m_size.x, m_size.y), ImGuiCond_Always);
            m_sizeChanged = false;
        }
    }

    void TransformablePanel::copyImGuiSize()
    {
        ImVec2 size = ImGui::GetWindowSize();
        m_size = glm::vec2(size.x, size.y);

        size = ImGui::GetContentRegionAvail();
        m_contentSize = glm::vec2(size.x, size.y);
    }

    void TransformablePanel::copyImGuiPosition()
    {
        ImVec2 pos = ImGui::GetWindowPos();
        m_position = glm::vec2(pos.x, pos.y);
    }

    void TransformablePanel::Update()
    {
        if (!m_firstFrame)
        {
            if (!m_autoSize)
                updateSize();
            copyImGuiSize();

            updatePosition();
            copyImGuiPosition();
        }

        m_firstFrame = false;
    }

    glm::vec2 TransformablePanel::calculatePositionAlignmentOffset(bool default)
    {
        glm::vec2 result(0.0f);

        switch (default ? m_defaultHorizontalAlignment : m_horizontalAlignment)
        {
            case Settings::EHorizontalAlignment::Middle:
            {
                result.x -= m_size.x / 2.0f;
                break;
            }
            case Settings::EHorizontalAlignment::Right:
            {
                result.x -= m_size.x;
                break;
            }
        }

        switch (default ? m_defaultVerticalAlignment : m_verticalAlignment)
        {
            case Settings::EVerticalAlignment::Middle:
            {
                result.y -= m_size.y / 2.0f;
                break;
            }
            case Settings::EVerticalAlignment::Bottom:
            {
                result.y -= m_size.y;
                break;
            }
        }

        return result;
    }
}
