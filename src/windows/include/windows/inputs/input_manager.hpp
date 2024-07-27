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
#include "windows/cursor/cursor_mode.hpp"
#include "windows/cursor/cursor_shape.hpp"
#include "windows/glfw.hpp"

namespace Engine::Windows::Inputs
{
    class InputManager : public Tools::Services::IService
    {
    public:
        InputManager(Windows::GLFW* window);
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

        void SetCursorPosition(glm::dvec2 position) { glfwSetCursorPos(m_window->GetWindow(), position.x, position.y); }
        glm::dvec2 GetCursorPosition() const;

        void SetCursorMode(Cursor::ECursorMode mode);
        void SetCursorShape(Cursor::ECursorShape cursor);

        void ClearEvents();

        Tools::Eventing::Event<EKey> KeyPressedEvent;
        Tools::Eventing::Event<EKey> KeyReleasedEvent;
        Tools::Eventing::Event<EMouseButton> MouseButtonPressedEvent;
        Tools::Eventing::Event<EMouseButton> MouseButtonReleasedEvent;
        Tools::Eventing::Event<glm::dvec2> CursorMoveEvent;

    private:
        Windows::GLFW* m_window = nullptr;

        std::unordered_map<Cursor::ECursorShape, GLFWcursor*> m_cursors;
    };
}

#endif // ENGINE_WINDOWS_INPUTS_INPUT_MANAGER_HPP_
