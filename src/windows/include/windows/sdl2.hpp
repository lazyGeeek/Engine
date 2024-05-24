#pragma once
#ifndef ENGINE_WINDOWS_SDL2_HPP_
#define ENGINE_WINDOWS_SDL2_HPP_

#include <memory>
#include <unordered_map>

#define SDL_MAIN_HANDLED
#include <sdl2/SDL.h>

#include <glm/glm.hpp>

#include "settings/window_settings.hpp"
#include "tools/eventing/event.hpp"
#include "tools/services/service_interface.hpp"
#include "windows/cursor/cursor_shape.hpp"

namespace Engine::Windows
{
    namespace Inputs { class InputManager; }

    class SDL2 : public Tools::Services::IService
    {
    public:
        SDL2(const Settings::WindowSettings& windowSettings);
        virtual ~SDL2();

        SDL2(const SDL2& other)             = delete;
        SDL2(SDL2&& other)                  = delete;
        SDL2& operator=(const SDL2& other)  = delete;
        SDL2& operator=(const SDL2&& other) = delete;

        void SetSize(glm::i32vec2 size) { SDL_SetWindowSize(m_window, size.x, size.y); }
        void SetPosition(glm::i32vec2 position) { SDL_SetWindowPosition(m_window, position.x, position.y); }
        void SetMinimumSize(glm::i32vec2 size);
        void SetMaximumSize(glm::i32vec2 size);
        void SetFullscreen(bool value);
        void SetTitle(const std::string& title);

        void Minimize() const { SDL_MinimizeWindow(m_window); }
        void Maximize() const { SDL_MaximizeWindow(m_window); }
        void Restore()  const { SDL_RestoreWindow(m_window); }
        void Hide()     const { SDL_HideWindow(m_window); }
        void Show()     const { SDL_ShowWindow(m_window); }
        void Focus()    const { SDL_SetWindowInputFocus(m_window); }

        bool ShouldClose() const { return !m_window; }

        void ToggleFullscreen() { SetFullscreen(!IsFullscreen()); }

        bool IsFullscreen() const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_FULLSCREEN; }
        bool IsHidden()     const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_HIDDEN; }
        bool IsVisible()    const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_SHOWN; }
        bool IsMaximized()  const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_MAXIMIZED; }
        bool IsMinimized()  const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED; }
        bool IsFocused()    const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_INPUT_FOCUS; }
        bool IsResizable()  const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_RESIZABLE; }
        bool IsDecorated()  const { return SDL_GetWindowFlags(m_window) & SDL_WINDOW_BORDERLESS; }

        void PollEvents();
        void SwapBuffers() const { SDL_GL_SwapWindow(m_window); }

        std::string GetTitle() const { return m_settings.Title; }

        glm::i32vec2 GetMonitorSize()   const;
        glm::i32vec2 GetSize()          const;
        glm::i32vec2 GetMinimumSize()   const { return m_settings.MinimumSize; }
        glm::i32vec2 GetMaximumSize()   const { return m_settings.MaximumSize; }
        glm::i32vec2 GetPosition()      const;

        SDL_Window* GetWindow() const { return m_window; }
        SDL_GLContext GetContext() const { return m_context; }

        Inputs::InputManager& getInputManager() const;

        void CloseWindow();

        Tools::Eventing::Event<glm::i32vec2> ResizeEvent;
        Tools::Eventing::Event<glm::i32vec2> WindowMoveEvent;

        Tools::Eventing::Event<> MinimizeEvent;
        Tools::Eventing::Event<> MaximizeEvent;
        Tools::Eventing::Event<> RestoreEvent;
        Tools::Eventing::Event<> LostFocusEvent;
        Tools::Eventing::Event<> GainFocusEvent;
        Tools::Eventing::Event<> CloseEvent;

    private:
        void createSDL2Window(const Settings::WindowSettings& windowSettings);
        void destroyWindow();

        void onResize(glm::i32vec2 size) { m_settings.Size = size; }

        SDL_Window* m_window = nullptr;
        SDL_GLContext m_context;
        std::unique_ptr< Inputs::InputManager > m_inputManager = nullptr;

        Settings::WindowSettings m_settings;
    };
}

#endif // ENGINE_WINDOWS_SDL2_HPP_
