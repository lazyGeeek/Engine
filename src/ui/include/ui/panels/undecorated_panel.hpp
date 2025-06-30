#pragma once
#ifndef ENGINE_UI_PANELS_UNDECORATED_PANEL_HPP_
#define ENGINE_UI_PANELS_UNDECORATED_PANEL_HPP_

#include <glm/glm.hpp>

#include "transformable_panel.hpp"

namespace Engine::UI::Panels
{
    class UndecoratedPanel : public TransformablePanel
    {
    public:
        UndecoratedPanel()          = default;
        virtual ~UndecoratedPanel() = default;

        UndecoratedPanel(const UndecoratedPanel& other)             = delete;
        UndecoratedPanel(UndecoratedPanel&& other)                  = delete;
        UndecoratedPanel& operator=(const UndecoratedPanel& other)  = delete;
        UndecoratedPanel& operator=(const UndecoratedPanel&& other) = delete;

    protected:
        virtual void DrawImpl() override;

    private:
        int collectFlags();
    };
}

#endif // ENGINE_UI_PANELS_UNDECORATED_PANEL_HPP_
