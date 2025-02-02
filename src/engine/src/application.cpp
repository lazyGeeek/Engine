#include "engine/application.hpp"

#include "logs/logger.hpp"
#include "renderer/driver.hpp"
#include "renderer/open_gl.hpp"
#include "tools/services/service_locator.hpp"
#include "tools/time/global_clock.hpp"
#include "ui/ui_manager.hpp"
#include "windows/glfw.hpp"

#include "hardware_info/profiler_panel.hpp"

namespace Engine
{
    Application::Application(std::filesystem::path projectPath)
        : ProjectPath(projectPath)
    {
        Tools::Services::ServiceLocator::Provide<Tools::Time::GlobalClock>().Start();
        Windows::Settings::WindowSettings windowSettings;
        Windows::GLFW& window  = Tools::Services::ServiceLocator::Provide<Windows::GLFW>(windowSettings);
        Tools::Services::ServiceLocator::Provide<Renderer::Driver>(true);
        Tools::Services::ServiceLocator::Provide<Renderer::OpenGL>();
        UI::UIManager& manager = Tools::Services::ServiceLocator::Provide<UI::UIManager>(ProjectPath / "Configs\\ImGui.ini", "#version 460");
        manager.EnableDocking(true);
        manager.ApplyStyle(UI::Styling::EStyle::CustomDark);
        manager.LoadFont("PixelOperator", ProjectPath / "Configs\\Fonts\\PixelOperator.ttf", 12);
        manager.UseFont("PixelOperator");
    }

    Application::~Application()
    {
        Tools::Services::ServiceLocator::UnregisterService<UI::UIManager>();
        Tools::Services::ServiceLocator::UnregisterService<Renderer::OpenGL>();
        Tools::Services::ServiceLocator::UnregisterService<Renderer::Driver>();
        Tools::Services::ServiceLocator::UnregisterService<Windows::GLFW>();
        Tools::Services::ServiceLocator::UnregisterService<Tools::Time::GlobalClock>();
    }

    void Application::Run()
    {
        Windows::GLFW& window = Tools::Services::ServiceLocator::Get<Windows::GLFW>();
        Tools::Time::GlobalClock& clock = Tools::Services::ServiceLocator::Get<Tools::Time::GlobalClock>();
        UI::UIManager& uiManager = Tools::Services::ServiceLocator::Get<UI::UIManager>();
        Renderer::OpenGL& renderer = Tools::Services::ServiceLocator::Get<Renderer::OpenGL>();
        UI::UIManager& manager = Tools::Services::ServiceLocator::Get<UI::UIManager>();

        std::shared_ptr<UI::Modules::Canvas> canvas = std::make_shared<UI::Modules::Canvas>();
        canvas->SetDockspace(true);
        manager.SetCanvas(canvas);

        std::shared_ptr<HardwareInfo::ProfilerPanel> profiler = canvas->AddPanel<HardwareInfo::ProfilerPanel>();
        profiler->SetSize(glm::vec2(300.0f, 500.0f));

        while (IsRunning())
        {
            clock.UpdateDelta();
            window.PollEvents();
            renderer.Clear();
            renderer.SetClearColor(0.0f, 0.0f, 0.0f);
            uiManager.Render();
            window.SwapBuffers();
        }
    }

    bool Application::IsRunning() const
    {
        return !Tools::Services::ServiceLocator::Get<Windows::GLFW>().ShouldClose();
    }
}
