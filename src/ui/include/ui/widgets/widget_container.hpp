#pragma once
#ifndef ENGINE_UI_WIDGETS_WIDGET_CONTAINER_HPP_
#define ENGINE_UI_WIDGETS_WIDGET_CONTAINER_HPP_

#include <list>
#include <memory>

#include "ui/internal/memory_mode.hpp"

namespace Engine::UI::Widgets
{
    class BaseWidget;

    class WidgetContainer
    {
    public:
        WidgetContainer()          = default;
        virtual ~WidgetContainer() = default;

        WidgetContainer(const WidgetContainer& other)             = delete;
        WidgetContainer(WidgetContainer&& other)                  = delete;
        WidgetContainer& operator=(const WidgetContainer& other)  = delete;
        WidgetContainer& operator=(const WidgetContainer&& other) = delete;

        template <typename T, typename... Args>
        std::shared_ptr<T> CreateWidget(Args&&... args)
        {
            static_assert(std::is_base_of<BaseWidget, T>::value, "T should derive from BaseWidget");

            std::shared_ptr<T> instance = std::make_shared<T>(args...);
            AddWidget(instance, true);
            return instance;
        }

        void AddWidget(std::shared_ptr<BaseWidget> widget, bool manageMemory);
        void RemoveWidget(std::shared_ptr<BaseWidget> widget);
        void RemoveAllWidgets();
        void CollectGarbages();
        void DrawWidgets();
        void ReverseDrawOrder(bool reversed) { m_reversedDrawOrder = reversed; }

        const std::list<std::pair<std::shared_ptr<BaseWidget>, Internal::EMemoryMode>>& GetWidgets() const { return m_widgets; }

    protected:
        std::list<std::pair<std::shared_ptr<BaseWidget>, Internal::EMemoryMode>> m_widgets;
        bool m_reversedDrawOrder = false;
    };
}

#endif // ENGINE_UI_WIDGETS_WIDGET_CONTAINER_HPP_
