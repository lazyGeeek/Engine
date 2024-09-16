#pragma once
#ifndef ENGINE_UI_WIDGETS_BASE_WIDGET_HPP_
#define ENGINE_UI_WIDGETS_BASE_WIDGET_HPP_

#include <memory>
#include <string>

#include "ui/drawable_interface.hpp"
#include "ui/widgets/widget_container.hpp"

namespace Engine::UI::Widgets
{
    class BaseWidget : public IDrawable
    {
    public:
        BaseWidget();
        virtual ~BaseWidget() = default;

        BaseWidget(const BaseWidget& other)             = delete;
        BaseWidget(BaseWidget&& other)                  = delete;
        BaseWidget& operator=(const BaseWidget& other)  = delete;
        BaseWidget& operator=(const BaseWidget&& other) = delete;

        virtual bool Draw() override;
        void Destroy() { m_destroyed = true; }

        bool IsDestroyed() const { return m_destroyed; }

        bool HasParent() const       { return m_parent; }
        WidgetContainer* GetParent() { return m_parent; }

        const std::string& GetWidgetId() const { return m_widgetId; }

        void SetEnabled(bool enabled)   { m_enabled = enabled; }
        void SetSameLine(bool sameLine) { m_sameLine = sameLine; }

        bool IsEnabled()  const { return m_enabled; }
        bool IsSameLine() const { return m_sameLine; }

    protected:
        virtual void DrawImpl() = 0;

        WidgetContainer* m_parent = nullptr;

        std::string m_widgetId = "";

        bool m_enabled  = true;
        bool m_sameLine = false;

    private:
        friend void WidgetContainer::AddWidget(std::shared_ptr<BaseWidget> widget, bool manageMemory);
        friend void WidgetContainer::RemoveWidget(std::shared_ptr<BaseWidget> widget);
        friend void WidgetContainer::RemoveAllWidgets();

        static inline uint64_t m_id = 0;
        bool m_destroyed = false;
    };
}

#endif // ENGINE_UI_WIDGETS_BASE_WIDGET_HPP_
