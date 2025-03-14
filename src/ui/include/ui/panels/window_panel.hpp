#pragma once
#ifndef ENGINE_UI_PANELS_WINDOW_PANEL_HPP_
#define ENGINE_UI_PANELS_WINDOW_PANEL_HPP_

#include "ui/panels/transformable_panel.hpp"
#include "ui/settings/panel_window_settings.hpp"
#include "tools/eventing/event.hpp"

namespace Engine::UI::Panels
{
    class WindowPanel : public TransformablePanel
    {
    public:
        WindowPanel
        (
            const std::string& name = "",
            bool opened = true,
            const Settings::PanelWindowSettings& windowSettings = Settings::PanelWindowSettings { },
            const glm::vec2& position                                 = glm::vec2(0.0f, 0.0f),
            const glm::vec2& size                                     = glm::vec2(1.0f, 1.0f),
            Settings::EVerticalAlignment defaultVerticalAlignment     = Settings::EVerticalAlignment::Top,
            Settings::EHorizontalAlignment defaultHorizontalAlignment = Settings::EHorizontalAlignment::Left
        );

        virtual ~WindowPanel();

        WindowPanel(const WindowPanel& other)             = delete;
        WindowPanel(WindowPanel&& other)                  = delete;
        WindowPanel& operator=(const WindowPanel& other)  = delete;
        WindowPanel& operator=(const WindowPanel&& other) = delete;

        void Open();
        void Close();
        void Focus();
        void SetOpened(bool value);
        bool IsAppearing() const;

        bool IsOpened() const  { return m_opened; }
        bool IsHovered() const { return m_hovered; }
        bool IsFocused() const { return m_focused; }

        void ScrollToBottom() { m_mustScrollToBottom = true; }
        void ScrollToTop()    { m_mustScrollToTop    = true; }
        void ScrollToRight()  { m_mustScrollToRight  = true; }
        void ScrollToLeft()   { m_mustScrollToLeft   = true; }

        bool IsScrolledToBottom() const { return m_mustScrollToBottom; }
        bool IsScrolledToTop()    const { return m_mustScrollToTop; }
        bool IsScrolledToRight()  const { return m_mustScrollToRight; }
        bool IsScrolledToLeft()   const { return m_mustScrollToLeft; }

        bool IsAutoSize() const { return m_autoSize; }
        void SetAutoSize(bool autoSize) { m_autoSize = autoSize; }

        bool IsPaddingsDisabled() const { return m_disablePaddings; }
        void DisablePaddings(bool value) { m_disablePaddings = value; }

        Tools::Eventing::Event<> OpenEvent;
        Tools::Eventing::Event<> CloseEvent;

    protected:
        void DrawImpl() override;

        std::string m_name = "";

        glm::vec2 m_minSize = glm::vec2(0.0f, 0.0f);
        glm::vec2 m_maxSize = glm::vec2(0.0f, 0.0f);

        Settings::PanelWindowSettings m_windowSettings;

    private:
        bool m_opened             = true;
        bool m_hovered            = true;
        bool m_focused            = true;
        bool m_scrolledToBottom   = false;
        bool m_scrolledToTop      = false;

        bool m_mustScrollToBottom = false;
        bool m_mustScrollToTop    = false;
        bool m_mustScrollToRight  = false;
        bool m_mustScrollToLeft   = false;

        bool m_disablePaddings    = false;
    };
}

#endif // ENGINE_UI_PANELS_PANEL_WINDOW_HPP_
