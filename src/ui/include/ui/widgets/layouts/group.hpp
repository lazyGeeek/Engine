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

    protected:
        virtual void DrawImpl() override;

        Settings::GroupWidgetSettings m_groupSettings;
    };
}

#endif // ENGINE_UI_WIDGETS_LAYOUTS_GROUP_HPP_
