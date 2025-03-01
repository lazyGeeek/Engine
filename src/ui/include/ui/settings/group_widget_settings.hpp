#pragma once
#ifndef ENGINE_UI_SETTINGS_GROUP_WIDGET_SETTINGS_HPP_
#define ENGINE_UI_SETTINGS_GROUP_WIDGET_SETTINGS_HPP_

namespace Engine::UI::Settings
{
    struct GroupWidgetSettings
    {
        bool Border                 = true;
        bool AlwaysUseWindowPadding = true;
        bool ResizeX                = false;
        bool ResizeY                = false;
        bool AutoResizeX            = false;
        bool AutoResizeY            = false;
        //bool AlwaysAutoResize       = false;
        bool FrameStyle             = true;
    };
}

#endif // ENGINE_UI_SETTINGS_GROUP_WIDGET_SETTINGS_HPP_
