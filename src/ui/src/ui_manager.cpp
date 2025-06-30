#include "ui/ui_manager.hpp"
#include "tools/services/service_locator.hpp"
#include "windows/glfw.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace Engine::UI
{
    UIManager::UIManager(const std::filesystem::path& saveFile, const std::string& glslVersion)
    {
        ImGui::CreateContext();
        ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

        SetEditorLayoutSaveFilename(saveFile);

        m_currentCanvas = std::make_shared<UI::Modules::Canvas>();

        ImGui_ImplGlfw_InitForOpenGL(Tools::Services::ServiceLocator::Get<Windows::GLFW>().GetWindow(), true);
        ImGui_ImplOpenGL3_Init(glslVersion.c_str());
    }

    UIManager::~UIManager()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        m_fonts.clear();
    }

    void UIManager::ApplyStyle(UI::Styling::EStyle style)
    {
        ImGuiStyle* newStyle = &ImGui::GetStyle();
    
        switch (style)
        {
            case UI::Styling::EStyle::ImClassicStyle: ImGui::StyleColorsClassic(); break;
            case UI::Styling::EStyle::ImDarkStyle:    ImGui::StyleColorsDark();    break;
            case UI::Styling::EStyle::ImLightStyle:   ImGui::StyleColorsLight();   break;
        }
    
        if (style == UI::Styling::EStyle::CustomDark)
        {
            newStyle->WindowPadding     = ImVec2(15, 15);
            newStyle->WindowRounding    = 3.0f;
            newStyle->FramePadding      = ImVec2(5, 5);
            newStyle->FrameRounding     = 3.0f;
            newStyle->ItemSpacing       = ImVec2(12, 8);
            newStyle->ItemInnerSpacing  = ImVec2(8, 6);
            newStyle->IndentSpacing     = 25.0f;
            newStyle->ScrollbarSize     = 15.0f;
            newStyle->ScrollbarRounding = 5.0f;
            newStyle->GrabMinSize       = 5.0f;
            newStyle->GrabRounding      = 0.0f;
            newStyle->TabRounding       = 0.0f;
            newStyle->ChildRounding     = 0.0f;
            newStyle->PopupRounding     = 0.0f;
    
            newStyle->WindowBorderSize = 1.0f;
            newStyle->FrameBorderSize  = 0.0f;
            newStyle->PopupBorderSize  = 1.0f;

            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_Text]                  = ImVec4(0.96f, 0.96f, 0.99f, 1.00f);
            colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
            colors[ImGuiCol_WindowBg]              = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
            colors[ImGuiCol_ChildBg]               = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
            colors[ImGuiCol_PopupBg]               = ImVec4(0.06f, 0.06f, 0.07f, 1.00f);
            colors[ImGuiCol_Border]                = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
            colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg]               = ImVec4(0.12f, 0.12f, 0.13f, 1.00f);
            colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
            colors[ImGuiCol_FrameBgActive]         = ImVec4(0.27f, 0.27f, 0.29f, 1.00f);
            colors[ImGuiCol_TitleBg]               = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
            colors[ImGuiCol_TitleBgActive]         = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
            colors[ImGuiCol_MenuBarBg]             = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
            colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
            colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.32f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.42f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.53f, 1.00f);
            colors[ImGuiCol_CheckMark]             = ImVec4(0.44f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_SliderGrab]            = ImVec4(0.44f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.59f, 0.59f, 0.61f, 1.00f);
            colors[ImGuiCol_Button]                = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
            colors[ImGuiCol_ButtonHovered]         = ImVec4(0.44f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_ButtonActive]          = ImVec4(0.59f, 0.59f, 0.61f, 1.00f);
            colors[ImGuiCol_Header]                = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
            colors[ImGuiCol_HeaderHovered]         = ImVec4(0.44f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_HeaderActive]          = ImVec4(0.59f, 0.59f, 0.61f, 1.00f);
            colors[ImGuiCol_Separator]             = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
            colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.44f, 0.44f, 0.47f, 0.39f);
            colors[ImGuiCol_SeparatorActive]       = ImVec4(0.44f, 0.44f, 0.47f, 0.59f);
            colors[ImGuiCol_ResizeGrip]            = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
            colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
            colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
            colors[ImGuiCol_Tab]                   = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
            colors[ImGuiCol_TabHovered]            = ImVec4(0.44f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_TabActive]             = ImVec4(0.44f, 0.44f, 0.47f, 1.00f);
            colors[ImGuiCol_TabUnfocused]          = ImVec4(0.20f, 0.20f, 0.22f, 0.39f);
            colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.44f, 0.44f, 0.47f, 0.39f);
            colors[ImGuiCol_DockingPreview]        = ImVec4(0.91f, 0.62f, 0.00f, 0.78f);
            colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
            colors[ImGuiCol_PlotLines]             = ImVec4(0.96f, 0.96f, 0.99f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.12f, 1.00f, 0.12f, 1.00f);
            colors[ImGuiCol_PlotHistogram]         = ImVec4(0.96f, 0.96f, 0.99f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.12f, 1.00f, 0.12f, 1.00f);
            colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            colors[ImGuiCol_DragDropTarget]        = ImVec4(0.91f, 0.62f, 0.00f, 1.00f);
            colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        }
    }

    bool UIManager::LoadFont(const std::string& id, const std::filesystem::path& fontFile, float fontSize)
    {
        if (m_fonts.count(id) == 0)
        {
            auto& io = ImGui::GetIO();
            ImFont* fontInstance = io.Fonts->AddFontFromFileTTF(fontFile.string().c_str(), fontSize);

            if (fontInstance)
            {
                m_fonts[id] = fontInstance;
                return true;
            }
        }

        return false;
    }

    bool UIManager::UnloadFont(const std::string& id)
    {
        if (m_fonts.count(id) > 0)
        {
            m_fonts.erase(id);
            return true;
        }

        return false;
    }

    bool UIManager::UseFont(const std::string& id)
    {
        auto foundFont = m_fonts.find(id);

        if (foundFont != m_fonts.end())
        {
            ImGui::GetIO().FontDefault = foundFont->second;
            return true;
        }

        return false;
    }

    void UIManager::UseDefaultFont()
    {
        ImGui::GetIO().FontDefault = nullptr;
    }

    void UIManager::EnableEditorLayoutSave(bool value)
    {
        if (value)
            ImGui::GetIO().IniFilename = m_layoutSaveFilename.c_str();
        else
            ImGui::GetIO().IniFilename = nullptr;
    }

    bool UIManager::IsEditorLayoutSaveEnabled() const
    {
        return ImGui::GetIO().IniFilename != nullptr;
    }

    void UIManager::SetEditorLayoutSaveFilename(const std::filesystem::path& file)
    {
        m_layoutSaveFilename = file.string();

        if (IsEditorLayoutSaveEnabled())
            ImGui::GetIO().IniFilename = m_layoutSaveFilename.c_str();
    }

    void UIManager::ResetLayout(const std::filesystem::path& file) const
    {
        ImGui::LoadIniSettingsFromDisk(file.string().c_str());
    }

    void UIManager::SetEditorLayoutAutosaveFrequency(float frequency)
    {
        ImGui::GetIO().IniSavingRate = frequency;
    }

    float UIManager::GetEditorLayoutAutosaveFrequency()
    {
        return ImGui::GetIO().IniSavingRate;
    }

    void UIManager::EnableDocking(bool value)
    {
        m_dockingState = value;
    
        if (value)
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        else
            ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;
    }

    void UIManager::SetCanvas(std::shared_ptr<Modules::Canvas> canvas)
    {
        RemoveCanvas();
        m_currentCanvas = canvas;
    }

    void UIManager::RemoveCanvas()
    {
        m_currentCanvas = nullptr;
    }

    void UIManager::Render()
    {
        if (m_currentCanvas && m_currentCanvas->Draw())
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
