#include "ui/widgets/layouts/tree_node.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Layouts
{
    TreeNode::TreeNode(const std::string& label, bool arrowClickToOpen)
        : BaseWidget(label),
          m_arrowClickToOpen { arrowClickToOpen } { }

    TreeNode::~TreeNode()
    {
        ClickedEvent.RemoveAllListeners();
        DoubleClickedEvent.RemoveAllListeners();
        OpenedEvent.RemoveAllListeners();
        ClosedEvent.RemoveAllListeners();
    }

    void TreeNode::Open()
    {
        m_shouldOpen = true;
        m_shouldClose = false;
    }

    void TreeNode::Close()
    {
        m_shouldClose = true;
        m_shouldOpen = false;
    }

    void TreeNode::DrawImpl()
    {
        if (!m_enabled)
            return;

        bool prevOpened = m_opened;

        if (m_shouldOpen)
        {
            ImGui::SetNextItemOpen(true);
            m_shouldOpen = false;
        }
        else if (m_shouldClose)
        {
            ImGui::SetNextItemOpen(false);
            m_shouldClose = false;
        }

        ImGuiTreeNodeFlags      flags = ImGuiTreeNodeFlags_None;
        if (m_arrowClickToOpen) flags |= ImGuiTreeNodeFlags_OpenOnArrow;
        if (m_selected)         flags |= ImGuiTreeNodeFlags_Selected;
        if (m_isLeaf)           flags |= ImGuiTreeNodeFlags_Leaf;

        bool opened = ImGui::TreeNodeEx((m_label + m_widgetId).c_str(), flags);

        if (ImGui::IsItemClicked() && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing())
        {
            ClickedEvent.Invoke();

            if (ImGui::IsMouseDoubleClicked(0))
                DoubleClickedEvent.Invoke();
        }

        if (opened)
        {
            if (!prevOpened)
                OpenedEvent.Invoke();

            m_opened = true;
            DrawWidgets();
            ImGui::TreePop();
        }
        else
        {
            if (prevOpened)
                ClosedEvent.Invoke();

            m_opened = false;
        }
    }
}
