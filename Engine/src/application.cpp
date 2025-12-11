#include "engine/application.hpp"
#include "renderer/device.hpp"
#include "renderer/vulkan.hpp"
#include "window/glfw.hpp"

#include <array>
#include <string>
#include <vector>

namespace Engine
{
    Application::Application(const std::filesystem::path& projectPath) :
        ProjectPath(projectPath),
        ConfigPath(projectPath / "Confings"),
        ShaderPath(projectPath / "Shaders")
    {
        if (!std::filesystem::exists(ConfigPath))
            std::filesystem::create_directory(ConfigPath);

        if (!std::filesystem::exists(ShaderPath))
            std::filesystem::create_directory(ShaderPath);

        Window::Settings::WindowSettings settings;
        settings.Title = "Engine";
        m_window = std::make_unique<Window::GLFW>(settings);

        m_device = std::make_unique<Renderer::Device>(m_window->GetWindow());

        m_renderer = std::make_unique<Renderer::Vulkan>();
        m_renderer->AddShader("vertex", ShaderPath / "vertex.spv");
        m_renderer->AddShader("fragment", ShaderPath / "fragment.spv");
    }

    Application::~Application()
    {
        if (m_renderer)
            m_renderer = nullptr;

        if (m_device)
            m_device = nullptr;

        if (m_window)
            m_window = nullptr;
    }

    void Application::Run()
    {
        while (m_window && !m_window->ShouldClose())
        {
            m_window->PollEvents();
        }
    }
}
