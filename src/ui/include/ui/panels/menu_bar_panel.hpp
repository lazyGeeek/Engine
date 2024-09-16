#pragma once
#ifndef ENGINE_UI_PANELS_MENU_BAR_PANEL_HPP_
#define ENGINE_UI_PANELS_MENU_BAR_PANEL_HPP_

#include "base_panel.hpp"

namespace Engine::UI::Panels
{
    class MenuBarPanel : public BasePanel
    {
    public:
        MenuBarPanel()          = default;
        virtual ~MenuBarPanel() = default;

        MenuBarPanel(const MenuBarPanel& other)             = delete;
        MenuBarPanel(MenuBarPanel&& other)                  = delete;
        MenuBarPanel& operator=(const MenuBarPanel& other)  = delete;
        MenuBarPanel& operator=(const MenuBarPanel&& other) = delete;

    protected:
        virtual void DrawImpl() override;
    };
}

#endif // ENGINE_UI_PANELS_MENU_BAR_PANEL_HPP_
