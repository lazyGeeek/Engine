#pragma once
#ifndef ENGINE_UI_WIDGETS_LAYOUTS_TREE_NODES_HPP_
#define ENGINE_UI_WIDGETS_LAYOUTS_TREE_NODES_HPP_

#include "tools/eventing/event.hpp"
#include "ui/widgets/base_widget.hpp"
#include "ui/widgets/widget_container.hpp"

namespace Engine::UI::Widgets::Layouts
{
    class TreeNode : public BaseWidget, public WidgetContainer
    {
    public:
        TreeNode(const std::string& label, bool arrowClickToOpen = false);
        virtual ~TreeNode() override;

        TreeNode(const TreeNode& other)             = delete;
        TreeNode(TreeNode&& other)                  = delete;
        TreeNode& operator=(const TreeNode& other)  = delete;
        TreeNode& operator=(const TreeNode&& other) = delete;

        void Open();
        void Close();

        bool IsOpened() const { return m_opened; }

        void SetSelected(bool selected) { m_selected = selected; }
        void SetAsLeaf(bool isLeaf)     { m_isLeaf   = isLeaf; }

        bool IsSelected() const { return m_selected; }
        bool IsLeaf() const     { return m_isLeaf; }

        Tools::Eventing::Event<> ClickedEvent;
        Tools::Eventing::Event<> DoubleClickedEvent;
        Tools::Eventing::Event<> OpenedEvent;
        Tools::Eventing::Event<> ClosedEvent;

    protected:
        virtual void DrawImpl() override;

        bool m_selected = false;
        bool m_isLeaf   = false;

    private:
        bool m_arrowClickToOpen = false;
        bool m_shouldOpen       = false;
        bool m_shouldClose      = false;
        bool m_opened           = false;

    };
}

#endif // ENGINE_UI_WIDGETS_LAYOUTS_TREE_NODES_HPP_
