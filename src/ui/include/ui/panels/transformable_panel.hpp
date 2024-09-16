#pragma once
#ifndef ENGINE_UI_PANELS_TRANSFORMABLE_PANEL_HPP_
#define ENGINE_UI_PANELS_TRANSFORMABLE_PANEL_HPP_

#include <glm/glm.hpp>

#include "base_panel.hpp"
#include "ui/settings/alignment.hpp"

namespace Engine::UI::Panels
{
    class TransformablePanel : public BasePanel
    {
    public:
        TransformablePanel
        (
            const glm::vec2& defaultPosition = glm::vec2(-1.0f, -1.0f),
            const glm::vec2& defaultSize     = glm::vec2(-1.0f, -1.0f),
            Settings::EVerticalAlignment defaultVerticalAlignment     = Settings::EVerticalAlignment::Top,
            Settings::EHorizontalAlignment defaultHorizontalAlignment = Settings::EHorizontalAlignment::Left,
            bool ignoreConfigFile = false
        );

        virtual ~TransformablePanel() { }

        TransformablePanel(const TransformablePanel& other)             = delete;
        TransformablePanel(TransformablePanel&& other)                  = delete;
        TransformablePanel& operator=(const TransformablePanel& other)  = delete;
        TransformablePanel& operator=(const TransformablePanel&& other) = delete;

        void SetPosition(const glm::vec2& position);
        void SetSize(const glm::vec2& size);

        void SetHorizontalAlignment(Settings::EHorizontalAlignment horizontalAlignment);
        void SetVerticalAlignment(Settings::EVerticalAlignment verticalAligment);

        const glm::vec2& GetPosition() const { return m_position; }
        const glm::vec2& GetSize() const     { return m_size; }

        Settings::EHorizontalAlignment GetHorizontalAlignment() const { return m_horizontalAlignment; }
        Settings::EVerticalAlignment GetVerticalAlignment() const     { return m_verticalAlignment; }

    protected:
        void Update();
        virtual void DrawImpl() = 0;

        glm::vec2 m_defaultPosition = glm::vec2(-1.0f);
        glm::vec2 m_defaultSize     = glm::vec2(-1.0f);

        Settings::EHorizontalAlignment m_defaultHorizontalAlignment = Settings::EHorizontalAlignment::Left;
        Settings::EVerticalAlignment m_defaultVerticalAlignment     = Settings::EVerticalAlignment::Top;

        bool m_ignoreConfigFile = true;

        glm::vec2 m_position = glm::vec2(0.0f);
        glm::vec2 m_size     = glm::vec2(0.0f);

        bool m_positionChanged  = false;
        bool m_sizeChanged      = false;
        bool m_alignmentChanged = false;

        Settings::EHorizontalAlignment m_horizontalAlignment = Settings::EHorizontalAlignment::Left;
        Settings::EVerticalAlignment m_verticalAlignment     = Settings::EVerticalAlignment::Top;

        bool m_firstFrame = true;
        bool m_autoSize   = true;

    private:
        glm::vec2 calculatePositionAlignmentOffset(bool default = false);

        void updatePosition();
        void updateSize();
        void copyImGuiPosition();
        void copyImGuiSize();
    };
}

#endif // ENGINE_UI_PANELS_TRANSFORMABLE_PANEL_HPP_
