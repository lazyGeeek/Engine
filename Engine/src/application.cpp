#include "engine/application.hpp"
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

        m_vulkan = std::make_shared<Renderer::Vulkan>(m_window->GetWindow());
        m_vulkan->Init(ShaderPath);

        m_window->ResizeEvent += [&, this](int32_t with, int32_t height)
        {
            m_vulkan->SetFramebufferResized();
        };
    }

    Application::~Application()
    {
        if (m_vulkan)
            m_vulkan = nullptr;

        if (m_window)
            m_window = nullptr;
    }

    void Application::Run()
    {
        while (m_window && !m_window->ShouldClose())
        {
            m_window->PollEvents();
            
            if (m_vulkan)
                m_vulkan->DrawFrame();
        }
    }
}
