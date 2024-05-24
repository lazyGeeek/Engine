#include "windows/inputs/input_manager.hpp"
#include "tools/services/service_locator.hpp"

#include <sdl2/SDL.h>

namespace Inputs = Engine::Windows::Inputs;

Inputs::InputManager::InputManager(Windows::SDL2* window) : m_window { window } { }

Inputs::InputManager::~InputManager()
{
    ClearEvents();
}

Inputs::EKeyState Inputs::InputManager::GetKeyState(Inputs::EKey key) const
{
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_GetScancodeFromKey(static_cast<int>(key))])
        return Inputs::EKeyState::Pressed;

    return Inputs::EKeyState::Released;
}

Inputs::EMouseButtonState Inputs::InputManager::GetMouseButtonState(Inputs::EMouseButton button) const
{
    if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(static_cast<int>(button)))
        return Inputs::EMouseButtonState::Pressed;

    return Inputs::EMouseButtonState::Released;
}

bool Inputs::InputManager::IsKeyPressed(EKey key) const
{
    return GetKeyState(key) == EKeyState::Pressed;
}

bool Inputs::InputManager::IsKeyReleased(EKey key) const
{
    return GetKeyState(key) == EKeyState::Released;
}

bool Inputs::InputManager::IsMouseButtonPressed(EMouseButton button) const
{
    return GetMouseButtonState(button) == EMouseButtonState::Pressed;
}

bool Inputs::InputManager::IsMouseButtonReleased(EMouseButton button) const
{
    return GetMouseButtonState(button) == EMouseButtonState::Released;
}

glm::i32vec2 Inputs::InputManager::GetMousePosition() const
{
    glm::i32vec2 state(-1);
    SDL_GetMouseState(&state.x, &state.y);
    return state;
}

void Inputs::InputManager::SetCursorShape(Cursor::ECursorShape cursorShape)
{
    SDL_Cursor* cursor = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursorShape));
    SDL_SetCursor(cursor);
}

void Inputs::InputManager::ClearEvents()
{
    KeyPressedEvent.RemoveAllListeners();
    KeyReleasedEvent.RemoveAllListeners();
    MouseButtonPressedEvent.RemoveAllListeners();
    MouseButtonReleasedEvent.RemoveAllListeners();
    CursorMoveEvent.RemoveAllListeners();
}
