#include "engine/application.hpp"

#include "tools/services/service_locator.hpp"
#include "tools/time/global_clock.hpp"
#include "windows/glfw.hpp"

namespace Engine
{
    Application::Application(std::filesystem::path projectPath)
        : ProjectPath(projectPath)
    {
        Tools::Services::ServiceLocator::Provide<Tools::Time::GlobalClock>().Start();
        Windows::Settings::WindowSettings windowSettings;
        Tools::Services::ServiceLocator::Provide<Windows::GLFW>(windowSettings);
    }

    Application::~Application()
    {
        Tools::Services::ServiceLocator::UnregisterService<Windows::GLFW>();
        Tools::Services::ServiceLocator::UnregisterService<Tools::Time::GlobalClock>();
    }

    void Application::Run()
    {
        Windows::GLFW& window = Tools::Services::ServiceLocator::Get<Windows::GLFW>();
        Tools::Time::GlobalClock& clock = Tools::Services::ServiceLocator::Get<Tools::Time::GlobalClock>();

        while (IsRunning())
        {
            clock.UpdateDelta();
            window.PollEvents();
            window.SwapBuffers();
        }
    }

    bool Application::IsRunning() const
    {
        return !Tools::Services::ServiceLocator::Get<Windows::GLFW>().ShouldClose();
    }
}
