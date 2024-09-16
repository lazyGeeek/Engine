#include "ui/panels/transformable_panel.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Panels
{
    TransformablePanel::TransformablePanel
    (
        const glm::vec2& defaultPosition, const glm::vec2& defaultSize,
        Settings::EVerticalAlignment defaultVerticalAlignment,
        Settings::EHorizontalAlignment defaultHorizontalAlignment,
        bool ignoreConfigFile
    ) : m_defaultPosition { defaultPosition },
        m_defaultSize { defaultSize },
        m_defaultVerticalAlignment { defaultVerticalAlignment },
        m_defaultHorizontalAlignment { defaultHorizontalAlignment },
        m_ignoreConfigFile { ignoreConfigFile }
    {
        SetPosition(m_defaultPosition);
        SetSize(m_defaultSize);
        SetVerticalAlignment(m_defaultVerticalAlignment);
        SetHorizontalAlignment(m_defaultHorizontalAlignment);
    }

    void TransformablePanel::SetPosition(const glm::vec2& position)
    {
        m_position = position;
        m_positionChanged = true;
    }

    void TransformablePanel::SetSize(const glm::vec2& size)
    {
        m_size = size;
        m_sizeChanged = true;
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

    void TransformablePanel::updatePosition()
    {
        if (m_defaultPosition != glm::vec2(-1.0))
        {
            glm::vec2 offsettedDefaultPos = m_defaultPosition + calculatePositionAlignmentOffset(true);
            ImGui::SetWindowPos(ImVec2(offsettedDefaultPos.x, offsettedDefaultPos.y), m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
        }

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

    void TransformablePanel::copyImGuiPosition()
    {
        ImVec2 pos = ImGui::GetWindowPos();
        m_position = glm::vec2(pos.x, pos.y);
    }

    void TransformablePanel::copyImGuiSize()
    {
        ImVec2 size = ImGui::GetWindowSize();
        m_size = glm::vec2(size.x, size.y);
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
            case Settings::EHorizontalAlignment::Center:
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
