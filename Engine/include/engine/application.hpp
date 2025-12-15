#pragma once
#ifndef ENGINE_APPLICATION_HPP_
#define ENGINE_APPLICATION_HPP_

#include <filesystem>
#include <memory>

namespace Renderer{ class Device; } // class Vulkan; }
namespace Window { class GLFW; }

namespace Engine
{
    class Application
    {
    public:
        Application(const std::filesystem::path& projectPath);
        ~Application();

        Application(const Application& other)             = delete;
        Application(Application&& other)                  = delete;
        Application& operator=(const Application& other)  = delete;
        Application& operator=(const Application&& other) = delete;

        void Run();

        const std::filesystem::path ProjectPath;
        const std::filesystem::path ConfigPath;
        const std::filesystem::path ShaderPath;

    private:
        std::unique_ptr<Window::GLFW> m_window = nullptr;
        std::shared_ptr<Renderer::Device> m_device = nullptr;
        // std::unique_ptr<Renderer::Vulkan> m_renderer = nullptr;
    };
}

#endif // ENGINE_APPLICATION_HPP_
