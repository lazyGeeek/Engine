#pragma once
#ifndef ENGINE_WINDOWS_INPUTS_INPUT_MANAGER_HPP_
#define ENGINE_WINDOWS_INPUTS_INPUT_MANAGER_HPP_

#include <unordered_map>

#include <glm/glm.hpp>

#include "key.hpp"
#include "key_state.hpp"
#include "mouse_button.hpp"
#include "mouse_button_state.hpp"
#include "tools/eventing/event.hpp"
#include "tools/services/service_interface.hpp"
#include "windows/sdl2.hpp"

namespace Engine::Windows::Inputs
{
    class InputManager : public Tools::Services::IService
    {
    public:
        InputManager(Windows::SDL2* window);
        ~InputManager();

        InputManager(const InputManager& other)             = delete;
        InputManager(InputManager&& other)                  = delete;
        InputManager& operator=(const InputManager& other)  = delete;
        InputManager& operator=(const InputManager&& other) = delete;

        EKeyState GetKeyState(EKey key) const;
        EMouseButtonState GetMouseButtonState(EMouseButton button) const;

        bool IsKeyPressed(EKey key) const;
        bool IsKeyReleased(EKey key) const;
        bool IsMouseButtonPressed(EMouseButton button) const;
        bool IsMouseButtonReleased(EMouseButton button) const;

        void SetMousePosition(glm::i32vec2 position) { SDL_WarpMouseInWindow(m_window->GetWindow(), position.x, position.y); }
        glm::i32vec2 GetMousePosition() const;

        void ShowCursor(bool state) { SDL_ShowCursor(state ? SDL_ENABLE : SDL_DISABLE); }
        void SetRelativeMouseMode(bool lock) { SDL_SetRelativeMouseMode(lock ? SDL_TRUE : SDL_FALSE); }
        void SetCursorShape(Cursor::ECursorShape cursor);

        void ClearEvents();

        Tools::Eventing::Event<EKey> KeyPressedEvent;
        Tools::Eventing::Event<EKey> KeyReleasedEvent;
        Tools::Eventing::Event<EMouseButton> MouseButtonPressedEvent;
        Tools::Eventing::Event<EMouseButton> MouseButtonReleasedEvent;
        Tools::Eventing::Event<glm::i32vec2> CursorMoveEvent;

    private:
        Windows::SDL2* m_window = nullptr;
    };
}

#endif // ENGINE_WINDOWS_INPUTS_INPUT_MANAGER_HPP_
