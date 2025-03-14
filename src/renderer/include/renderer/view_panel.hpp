#pragma once
#ifndef ENGINE_RENDERER_VIEW_PANEL_HPP_
#define ENGINE_RENDERER_VIEW_PANEL_HPP_

#include <filesystem>

#include "renderer/open_gl.hpp"
#include "buffers/frame_buffer.hpp"
#include "ui/panels/window_panel.hpp"

namespace Engine::UI::Widgets::Visuals { class Image; }
namespace Engine::Renderer::Resources { class Model;  class Shader; }

namespace Engine::Renderer
{
    class ViewPanel : public UI::Panels::WindowPanel
    {
    public:
        ViewPanel(const std::filesystem::path& projectPath);

        ViewPanel(const ViewPanel& other)             = delete;
        ViewPanel(ViewPanel&& other)                  = delete;
        ViewPanel& operator=(const ViewPanel& other)  = delete;
        ViewPanel& operator=(const ViewPanel&& other) = delete;

    protected:
        void DrawImpl() override;

    private:
        OpenGL m_openGL;
        Buffers::FrameBuffer m_fbo;

        std::shared_ptr<UI::Widgets::Visuals::Image> m_renderImage = nullptr;
        std::shared_ptr<Resources::Shader> m_shader                = nullptr;
        std::shared_ptr<Resources::Model> m_cube                   = nullptr;
    };
}

#endif // ENGINE_RENDERER_VIEW_PANEL_HPP_
