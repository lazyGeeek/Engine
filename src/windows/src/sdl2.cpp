#include "windows/sdl2.hpp"

#include <stdexcept>

#include "logs/logger.hpp"
#include "tools/services/service_locator.hpp"
#include "windows/inputs/input_manager.hpp"

namespace Engine
{
    Windows::SDL2::SDL2(const Settings::WindowSettings& windowSettings)
        : m_settings{ windowSettings }
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER))
        {
            throw std::runtime_error(SDL_GetError());
            SDL_Quit();
        }

        createSDL2Window(windowSettings);

        m_inputManager = std::make_unique<Inputs::InputManager>(this);

        ResizeEvent += std::bind(&SDL2::onResize, this, std::placeholders::_1);
    }

    Windows::SDL2::~SDL2()
    {
        if (m_inputManager)
            m_inputManager = nullptr;

        CloseWindow();
        SDL_Quit();
    }

    void Windows::SDL2::createSDL2Window(const Settings::WindowSettings& windowSettings)
    {
        m_window = SDL_CreateWindow("",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_settings.Size.x,
            m_settings.Size.y,
            static_cast<Uint32>(windowSettings.Flags));

        if (!m_window)
            throw std::runtime_error("Failed to create SDL2 window");

        SDL_SetWindowMinimumSize(m_window, m_settings.MinimumSize.x, m_settings.MinimumSize.y);
        SDL_SetWindowMaximumSize(m_window, m_settings.MaximumSize.x, m_settings.MaximumSize.y);

        m_context = SDL_GL_CreateContext(m_window);

        if (m_context == NULL)
            throw std::runtime_error("OPENGL: Can't create SDL context");

        SDL_GL_MakeCurrent(m_window, m_context);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, windowSettings.Samples);
    }

    void Windows::SDL2::destroyWindow()
    {
        if (m_window)
        {
            SDL_GL_DeleteContext(m_context);
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }

    void Windows::SDL2::CloseWindow()
    {
        ResizeEvent.RemoveAllListeners();
        destroyWindow();
    }

    void Windows::SDL2::PollEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
                    Inputs::EKey key = static_cast<Inputs::EKey>(event.key.keysym.sym);
                    m_inputManager->KeyPressedEvent.Invoke(key);
                    break;
                }
                case SDL_KEYUP:
                {
                    Inputs::EKey key = static_cast<Inputs::EKey>(event.key.keysym.sym);
                    m_inputManager->KeyReleasedEvent.Invoke(key);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    Inputs::EMouseButton button = static_cast<Inputs::EMouseButton>(event.button.button);
                    m_inputManager->MouseButtonPressedEvent.Invoke(button);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    Inputs::EMouseButton button = static_cast<Inputs::EMouseButton>(event.button.button);
                    m_inputManager->MouseButtonReleasedEvent.Invoke(button);
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    glm::i32vec2 motion(event.motion.x, event.motion.y);
                    m_inputManager->CursorMoveEvent.Invoke(motion);
                    break;
                }
                case SDL_WINDOWEVENT:
                {
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                        {
                            ResizeEvent.Invoke({ event.window.data1, event.window.data2 });
                            break;
                        }
                        case SDL_WINDOWEVENT_MOVED:
                        {
                            WindowMoveEvent.Invoke({ event.window.data1, event.window.data2 });
                            break;
                        }
                        case SDL_WINDOWEVENT_MINIMIZED:
                        {
                            MinimizeEvent.Invoke();
                            break;
                        }
                        case SDL_WINDOWEVENT_RESTORED:
                        {
                            RestoreEvent.Invoke();
                            break;
                        }
                        case SDL_WINDOWEVENT_MAXIMIZED:
                        {
                            MaximizeEvent.Invoke();
                            break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_GAINED:
                        {
                            GainFocusEvent.Invoke();
                            break;
                        }
                        case SDL_WINDOWEVENT_FOCUS_LOST:
                        {
                            LostFocusEvent.Invoke();
                            break;
                        }
                        case SDL_WINDOWEVENT_CLOSE:
                        {
                            CloseEvent.Invoke();
                            destroyWindow();
                            break;
                        }
                    }
                    break;
                }
                case SDL_QUIT:
                {
                    destroyWindow();
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    Windows::Inputs::InputManager& Windows::SDL2::getInputManager() const
    {
        if (!m_inputManager)
            throw std::runtime_error("Input Manager Destroyed");

        return *m_inputManager.get();
    }

    void Windows::SDL2::SetMinimumSize(glm::i32vec2 size)
    {
        m_settings.MinimumSize = size;
        SDL_SetWindowMinimumSize(m_window, size.x, size.y);
    }

    void Windows::SDL2::SetMaximumSize(glm::i32vec2 size)
    {
        m_settings.MaximumSize = size;
        SDL_SetWindowMaximumSize(m_window, size.x, size.y);
    }

    void Windows::SDL2::SetFullscreen(bool value)
    {
        SDL_SetWindowFullscreen(m_window, value ? 0 : SDL_WINDOW_FULLSCREEN);
    }

    void Windows::SDL2::SetTitle(const std::string& title)
    {
        m_settings.Title = title;
        SDL_SetWindowTitle(m_window, title.c_str());
    }

    glm::i32vec2 Windows::SDL2::GetMonitorSize() const
    {
        SDL_DisplayMode displayMode;

        if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
        {
            std::string message = "SDL_GetDesktopDisplayMode failed: ";
            std::string glewError = SDL_GetError();
            Logs::Logger::PrintLog(message + glewError, Logs::ELogLevel::Error);
            return { -1, -1 };
        }

        return { displayMode.w, displayMode.h };
    }

    glm::i32vec2 Windows::SDL2::GetSize() const
    {
        glm::i32vec2 size(-1);
        SDL_GetWindowSize(m_window, &size.x, &size.y);
        return size;
    }

    glm::i32vec2 Windows::SDL2::GetPosition() const
    {
        glm::i32vec2 pos(-1);
        SDL_GetWindowPosition(m_window, &pos.x, &pos.y);
        return pos;
    }
}