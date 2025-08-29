#include "engine/application.hpp"

// #include "hardware_info/profiler_panel.hpp"
// #include "logs/logger_panel.hpp"
#include "renderer/driver.hpp"
// #include "renderer/view_panel.hpp"
#include "tools/services/service_locator.hpp"
#include "tools/time/global_clock.hpp"
// #include "ui/ui_manager.hpp"
#include "windows/glfw.hpp"

namespace Engine
{
    Application::Application(const std::filesystem::path& projectPath) :
        ProjectPath(projectPath),
        ProjectShadersPath(projectPath / "Shaders")
    {
        Tools::Services::ServiceLocator::Provide<Tools::Time::GlobalClock>().Start();
        Windows::Settings::WindowSettings windowSettings;
        windowSettings.Resizable = true;
        Windows::GLFW& window  = Tools::Services::ServiceLocator::Provide<Windows::GLFW>(windowSettings);
        Tools::Services::ServiceLocator::Provide<Renderer::Driver>(ProjectShadersPath);
        // UI::UIManager& manager = Tools::Services::ServiceLocator::Provide<UI::UIManager>(ProjectPath / "Configs\\ImGui.ini", "#version 460");
        // manager.EnableDocking(true);
        // manager.ApplyStyle(UI::Styling::EStyle::CustomDark);
        // manager.LoadFont("PixelOperator", ProjectPath / "Configs\\Fonts\\PixelOperator.ttf", 16);
        // manager.UseFont("PixelOperator");
    }

    Application::~Application()
    {
        // Tools::Services::ServiceLocator::UnregisterService<UI::UIManager>();
        Tools::Services::ServiceLocator::UnregisterService<Renderer::Driver>();
        Tools::Services::ServiceLocator::UnregisterService<Windows::GLFW>();
        Tools::Services::ServiceLocator::UnregisterService<Tools::Time::GlobalClock>();
    }

    void Application::Run()
    {
        Windows::GLFW& window = Tools::Services::ServiceLocator::Get<Windows::GLFW>();
        Tools::Time::GlobalClock& clock = Tools::Services::ServiceLocator::Get<Tools::Time::GlobalClock>();
        Renderer::Driver& driver = Tools::Services::ServiceLocator::Get<Renderer::Driver>();
        driver.Init();
        // UI::UIManager& uiManager = Tools::Services::ServiceLocator::Get<UI::UIManager>();

        // std::shared_ptr<UI::Modules::Canvas> canvas = std::make_shared<UI::Modules::Canvas>();
        // canvas->SetDockspace(true);
        // uiManager.SetCanvas(canvas);

        // std::shared_ptr<HardwareInfo::ProfilerPanel> profiler = canvas->AddPanel<HardwareInfo::ProfilerPanel>();
        // profiler->Resize(glm::vec2(300.0f, 500.0f));

        // std::shared_ptr<Logs::LoggerPanel> console = canvas->AddPanel<Logs::LoggerPanel>();
        // console->Resize(glm::vec2(1000.0f, 250.0f));

        // std::shared_ptr<Renderer::ViewPanel> viewPanel = canvas->AddPanel<Renderer::ViewPanel>(ProjectPath);
        // viewPanel->Resize(glm::vec2(500.0f, 500.0f));

        while (IsRunning())
        {
            clock.UpdateDelta();
            window.PollEvents();
            driver.NewFrame();
            // uiManager.Render();
            // window.SwapBuffers();
        }

        driver.Release();
    }

    bool Application::IsRunning() const
    {
        return !Tools::Services::ServiceLocator::Get<Windows::GLFW>().ShouldClose();
    }
}
