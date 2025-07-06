#pragma once
#ifndef ENGINE_WINDOWS_SDL2_HPP_
#define ENGINE_WINDOWS_SDL2_HPP_

#include <memory>
#include <unordered_map>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "settings/window_settings.hpp"
#include "tools/eventing/event.hpp"
#include "tools/services/service_interface.hpp"

namespace Engine::Windows
{
    namespace Inputs { class InputManager; }

    class GLFW : public Tools::Services::IService
    {
    public:
        GLFW(const Settings::WindowSettings& windowSettings, bool fullscreen = false);
        virtual ~GLFW();

        GLFW(const GLFW& other)             = delete;
        GLFW(GLFW&& other)                  = delete;
        GLFW& operator=(const GLFW& other)  = delete;
        GLFW& operator=(const GLFW&& other) = delete;

        void SetSize(glm::i32vec2 size) { glfwSetWindowSize(m_window, size.x, size.y); }
        void SetPosition(glm::i32vec2 position) { glfwSetWindowPos(m_window, position.x, position.y); }
        void SetMinimumSize(glm::i32vec2 size);
        void SetMaximumSize(glm::i32vec2 size);
        void SetFullscreen(bool value);
        void SetTitle(const std::string& title);
        void SetVsync(bool vsync);
        void SetShouldClose(bool value) const { glfwSetWindowShouldClose(m_window, value); }

        void Minimize() const { glfwIconifyWindow(m_window); }
        void Maximize() const { glfwMaximizeWindow(m_window); }
        void Restore()  const { glfwRestoreWindow(m_window); }
        void Hide()     const { glfwHideWindow(m_window); }
        void Show()     const { glfwShowWindow(m_window); }
        void Focus()    const { glfwFocusWindow(m_window); }

        bool ShouldClose() const { return glfwWindowShouldClose(m_window); }

        void ToggleFullscreen() { SetFullscreen(!IsFullscreen()); }

        bool IsFullscreen() const { return m_fullscreen; }
        bool IsHidden()     const { return glfwGetWindowAttrib(m_window, GLFW_VISIBLE) == GLFW_FALSE; }
        bool IsVisible()    const { return glfwGetWindowAttrib(m_window, GLFW_VISIBLE) == GLFW_TRUE; }
        bool IsMaximized()  const { return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) == GLFW_TRUE; }
        bool IsMinimized()  const { return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) == GLFW_FALSE; }
        bool IsFocused()    const { return glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_TRUE; }
        bool IsResizable()  const { return glfwGetWindowAttrib(m_window, GLFW_RESIZABLE) == GLFW_TRUE; }
        bool IsDecorated()  const { return glfwGetWindowAttrib(m_window, GLFW_DECORATED) == GLFW_TRUE; }

        // void SwapBuffers() const { glfwSwapBuffers(m_window); }
        void PollEvents() const { glfwPollEvents(); }

        std::string GetTitle() const { return m_settings.Title; }

        glm::i32vec2 GetSize()          const;
        glm::i32vec2 GetMinimumSize()   const { return m_settings.MinimumSize; }
        glm::i32vec2 GetMaximumSize()   const { return m_settings.MaximumSize; }
        glm::i32vec2 GetPosition()      const;
        glm::i32vec2 GetFramebufferSize() const;

        bool HasVsync() const { return m_vsync; }

        GLFWwindow* GetWindow() const { return m_window; }

        Inputs::InputManager& getInputManager() const;

        void CloseWindow();

        void MakeCurrentContext() const { glfwMakeContextCurrent(m_window); }

        Tools::Eventing::Event<glm::i32vec2> ResizeEvent;
        Tools::Eventing::Event<glm::i32vec2> MoveEvent;
        Tools::Eventing::Event<glm::i32vec2> FramebufferResizeEvent;

        Tools::Eventing::Event<> MinimizeEvent;
        Tools::Eventing::Event<> MaximizeEvent;
        Tools::Eventing::Event<> RestoreEvent;
        Tools::Eventing::Event<> LostFocusEvent;
        Tools::Eventing::Event<> GainFocusEvent;
        Tools::Eventing::Event<> CloseEvent;

    private:
        void createGLFWWindow(const Settings::WindowSettings& windowSettings);

        void bindKeyCallback() const;
        void bindMouseCallback() const;
        void bindCursorMoveCallback() const;
        void bindResizeCallback() const;
        void bindFramebufferResizeCallback() const;
        void bindMoveCallback() const;
        void bindIconifyCallback() const;
        void bindFocusCallback() const;
        void bindCloseCallback() const;

        void onResize(glm::i32vec2 size) { m_settings.Size = size; }
        void onMove(glm::i32vec2 pos) { m_settings.Position = pos; }

        GLFWwindow* m_window = nullptr;
        std::unique_ptr<Inputs::InputManager> m_inputManager = nullptr;

        Settings::WindowSettings m_settings;
        bool m_fullscreen = false;
        bool m_vsync = false;
    };
}

#endif // ENGINE_WINDOWS_SDL2_HPP_
