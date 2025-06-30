#include "ui/widgets/widget_container.hpp"
#include "ui/widgets/base_widget.hpp"

#include <algorithm>

namespace Engine::UI::Widgets
{
    void WidgetContainer::AddWidget(std::shared_ptr<BaseWidget> widget, bool manageMemory)
    {
        Internal::EMemoryMode mode = manageMemory ? Internal::EMemoryMode::InternalManagment : Internal::EMemoryMode::ExternalManagment;

        auto& it = std::find_if(m_widgets.begin(), m_widgets.end(), [&widget](std::pair<std::shared_ptr<BaseWidget>, Internal::EMemoryMode>& pair)
        {
            return pair.first == widget;
        });

        if (it != m_widgets.end())
        {
            it->second = mode;
            return;
        }

        m_widgets.emplace_back(std::make_pair(widget, mode));

        if (widget->m_parent)
            widget->m_parent->RemoveWidget(widget);

        widget->m_parent = this;
    }

    void WidgetContainer::RemoveWidget(std::shared_ptr<BaseWidget> widget)
    {
        auto& it = std::remove_if(m_widgets.begin(), m_widgets.end(), [&widget](std::pair<std::shared_ptr<BaseWidget>, Internal::EMemoryMode>& pair)
        {
            return pair.first == widget;
        });

        if (it != m_widgets.end())
        {
            m_widgets.erase(it, m_widgets.end());
            widget->m_parent = nullptr;
        }
    }

    void WidgetContainer::RemoveAllWidgets()
    {
        for (auto& widget : m_widgets)
            widget.first->m_parent = nullptr;

        m_widgets.clear();
    }

    void WidgetContainer::CollectGarbages()
    {
        auto& it = std::remove_if(m_widgets.begin(), m_widgets.end(), [](std::pair<std::shared_ptr<BaseWidget>, Internal::EMemoryMode>& item)
        {
            return item.second == Internal::EMemoryMode::InternalManagment && item.first && item.first->IsDestroyed();
        });

        if (it != m_widgets.end())
            RemoveWidget(it->first);
    }

    void WidgetContainer::DrawWidgets()
    {
        CollectGarbages();

        if (m_reversedDrawOrder)
        {
            for (auto it = m_widgets.crbegin(); it != m_widgets.crend(); ++it)
                it->first->Draw();
        }
        else
        {
            for (const auto& widget : m_widgets)
                widget.first->Draw();
        }
    }
}
