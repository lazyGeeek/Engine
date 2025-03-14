#pragma once
#ifndef ENGINE_UI_WIDGETS_LAYOUTS_GROUP_HPP_
#define ENGINE_UI_WIDGETS_LAYOUTS_GROUP_HPP_

#include "ui/settings/group_widget_settings.hpp"
#include "ui/widgets/base_widget.hpp"
#include "ui/widgets/widget_container.hpp"

namespace Engine::UI::Widgets::Layouts
{
    class Group : public BaseWidget, public WidgetContainer
    {
    public:
        Group(const Settings::GroupWidgetSettings& groupSettings = Settings::GroupWidgetSettings { });
        virtual ~Group() override;

        Group(const Group& other)             = delete;
        Group(Group&& other)                  = delete;
        Group& operator=(const Group& other)  = delete;
        Group& operator=(const Group&& other) = delete;

        void SetSettings(const Settings::GroupWidgetSettings& settings) { m_groupSettings = settings; }
        Settings::GroupWidgetSettings GetSettings() const { return m_groupSettings; }

        void ScrollToBottom() { m_mustScrollToBottom = true; }
        void ScrollToTop()    { m_mustScrollToTop    = true; }
        void ScrollToRight()  { m_mustScrollToRight  = true; }
        void ScrollToLeft()   { m_mustScrollToLeft   = true; }

        bool IsScrolledToBottom() const { return m_mustScrollToBottom; }
        bool IsScrolledToTop()    const { return m_mustScrollToTop; }
        bool IsScrolledToRight()  const { return m_mustScrollToRight; }
        bool IsScrolledToLeft()   const { return m_mustScrollToLeft; }

    protected:
        virtual void DrawImpl() override;

        Settings::GroupWidgetSettings m_groupSettings;

    private:
        bool m_mustScrollToBottom = false;
        bool m_mustScrollToTop    = false;
        bool m_mustScrollToRight  = false;
        bool m_mustScrollToLeft   = false;
    };
}

#endif // ENGINE_UI_WIDGETS_LAYOUTS_GROUP_HPP_
