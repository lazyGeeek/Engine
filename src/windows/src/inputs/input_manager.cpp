#include "windows/inputs/input_manager.hpp"
#include "tools/services/service_locator.hpp"

namespace Inputs = Engine::Windows::Inputs;

Inputs::InputManager::InputManager(Windows::GLFW* window) : m_window { window }
{
    m_cursors[Cursor::ECursorShape::Arrow]     = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::Arrow));
    m_cursors[Cursor::ECursorShape::IBeam]     = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::IBeam));
    m_cursors[Cursor::ECursorShape::CrossHair] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::CrossHair));
    m_cursors[Cursor::ECursorShape::Hand]      = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::Hand));
    m_cursors[Cursor::ECursorShape::HResize]   = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::HResize));
    m_cursors[Cursor::ECursorShape::VResize]   = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::VResize));
}

Inputs::InputManager::~InputManager()
{
    ClearEvents();

    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::Arrow]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::IBeam]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::CrossHair]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::Hand]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::HResize]);
    glfwDestroyCursor(m_cursors[Cursor::ECursorShape::VResize]);
}

Inputs::EKeyState Inputs::InputManager::GetKeyState(Inputs::EKey key) const
{
    if (glfwGetKey(m_window->GetWindow(), static_cast<int>(key)) == GLFW_PRESS)
        return EKeyState::Pressed;

    return Inputs::EKeyState::Released;
}

Inputs::EMouseButtonState Inputs::InputManager::GetMouseButtonState(Inputs::EMouseButton button) const
{
    if (glfwGetMouseButton(m_window->GetWindow(), static_cast<int>(button)) == GLFW_PRESS)
        return EMouseButtonState::Pressed;

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

glm::dvec2 Inputs::InputManager::GetCursorPosition() const
{
    glm::dvec2 state(-1.0);
    glfwGetCursorPos(m_window->GetWindow(), &state.x, &state.y);
    return state;
}

void Inputs::InputManager::SetCursorMode(Cursor::ECursorMode mode)
{
    glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, static_cast<int>(mode));
}

void Inputs::InputManager::SetCursorShape(Cursor::ECursorShape cursorShape)
{
	glfwSetCursor(m_window->GetWindow(), m_cursors[cursorShape]);
}

void Inputs::InputManager::ClearEvents()
{
    KeyPressedEvent.RemoveAllListeners();
    KeyReleasedEvent.RemoveAllListeners();
    MouseButtonPressedEvent.RemoveAllListeners();
    MouseButtonReleasedEvent.RemoveAllListeners();
    CursorMoveEvent.RemoveAllListeners();
}
