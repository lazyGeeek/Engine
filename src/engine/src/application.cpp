#include "engine/application.hpp"

#include <iostream>

#include "logs/logger.hpp"
#include "tools/services/service_locator.hpp"
#include "tools/time/date.hpp"
#include "tools/time/global_clock.hpp"
#include "windows/inputs/input_manager.hpp"
#include "windows/sdl2.hpp"

namespace Engine
{
    Application::Application(std::filesystem::path projectPath)
        : ProjectPath(projectPath)
    {
        Tools::Services::ServiceLocator::Provide<Tools::Time::GlobalClock>().Start();

        Windows::Settings::WindowSettings windowSettings;
        windowSettings.Flags = Windows::Settings::ESDL2WindowFlags::OpenGL       |
                               Windows::Settings::ESDL2WindowFlags::AllowHighdpi |
                               Windows::Settings::ESDL2WindowFlags::InputFocus   |
                               Windows::Settings::ESDL2WindowFlags::Shown;

        Tools::Services::ServiceLocator::Provide<Windows::SDL2>(windowSettings);
    }

    Application::~Application()
    {
        Tools::Services::ServiceLocator::UnregisterService<Windows::SDL2>();
        Tools::Services::ServiceLocator::UnregisterService<Tools::Time::GlobalClock>();
    }

    void Application::Run()
    {
        Windows::SDL2& window = Tools::Services::ServiceLocator::Get<Windows::SDL2>();

        while (IsRunning())
        {
            Tools::Services::ServiceLocator::Get<Tools::Time::GlobalClock>().UpdateDelta();
            window.PollEvents();
        }
    }

    bool Application::IsRunning() const
    {
        return !Tools::Services::ServiceLocator::Get<Windows::SDL2>().ShouldClose();
    }
}
