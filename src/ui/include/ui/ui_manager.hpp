#pragma once
#ifndef ENGINE_UI_UI_MANAGER_HPP_
#define ENGINE_UI_UI_MANAGER_HPP_

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

#include "ui/modules/canvas.hpp"
#include "ui/styling/style.hpp"
#include "tools/services/service_interface.hpp"

class ImFont;

namespace Engine::UI
{
    class UIManager : public Tools::Services::IService
    {
    public:
        UIManager(const std::filesystem::path& saveFile, const std::string& glslVersion = "#version 150");
        virtual ~UIManager();

        UIManager(const UIManager& other)             = delete;
        UIManager(UIManager&& other)                  = delete;
        UIManager& operator=(const UIManager& other)  = delete;
        UIManager& operator=(const UIManager&& other) = delete;

        void ApplyStyle(Styling::EStyle style);
        bool LoadFont(const std::string& id, const std::filesystem::path& fontFile, float fontSize);
        bool UnloadFont(const std::string& id);
        bool UseFont(const std::string& id);
        void UseDefaultFont();
        void EnableEditorLayoutSave(bool value);
        bool IsEditorLayoutSaveEnabled() const;
        void SetEditorLayoutSaveFilename(const std::filesystem::path& file);
        void ResetLayout(const std::filesystem::path& file) const;
        void SetEditorLayoutAutosaveFrequency(float frequency);
        float GetEditorLayoutAutosaveFrequency();
        void EnableDocking(bool value);
        void SetCanvas(std::shared_ptr<Modules::Canvas> canvas);
        void RemoveCanvas();
        void Render();

        bool IsDockingEnabled() const { return m_dockingState; }

    private:
        bool m_dockingState = false;
        std::shared_ptr<Modules::Canvas> m_currentCanvas = nullptr;
        std::string m_layoutSaveFilename = "";
        std::unordered_map<std::string, ImFont*> m_fonts;
    };
}

#endif // ENGINE_UI_UI_MANAGER_HPP_
