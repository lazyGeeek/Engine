#include "windows/glfw.hpp"

#include <stdexcept>

#include "logs/logger.hpp"
#include "tools/services/service_locator.hpp"
#include "windows/inputs/input_manager.hpp"

namespace Engine::Windows
{
    GLFW::GLFW(const Settings::WindowSettings& windowSettings, bool fullscreen)
        : m_settings{ windowSettings },
          m_fullscreen { fullscreen }
    {
        createGLFWWindow(windowSettings);

        bindKeyCallback();
        bindMouseCallback();
        bindCursorMoveCallback();
        bindIconifyCallback();
        bindCloseCallback();
        bindResizeCallback();
        bindFramebufferResizeCallback();
        bindMoveCallback();
        bindFocusCallback();

        ResizeEvent.AddListener(std::bind(&GLFW::onResize, this, std::placeholders::_1));
        MoveEvent.AddListener(std::bind(&GLFW::onMove, this, std::placeholders::_1));

        m_inputManager = std::make_unique<Inputs::InputManager>(this);
    }

    GLFW::~GLFW()
    {
        if (m_inputManager)
            m_inputManager = nullptr;

        CloseWindow();
        glfwTerminate();
    }

    void GLFW::createGLFWWindow(const Settings::WindowSettings& windowSettings)
    {
        auto errorCallback = [](int code, const char* description)
        {
            Logs::Logger::PrintLog(description, Logs::ELogLevel::Error);
        };

        glfwSetErrorCallback(errorCallback);

        int initializationCode = glfwInit();

        if (initializationCode == GLFW_FALSE)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to Init GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, windowSettings.Samples);

        GLFWmonitor* selectedMonitor = nullptr;

        if (m_fullscreen)
            selectedMonitor = glfwGetPrimaryMonitor();

        glfwWindowHint(GLFW_RESIZABLE,    windowSettings.Resizable);
        glfwWindowHint(GLFW_DECORATED,    windowSettings.Decorated);
        glfwWindowHint(GLFW_FOCUSED,      windowSettings.Focused);
        glfwWindowHint(GLFW_MAXIMIZED,    windowSettings.Maximized);
        glfwWindowHint(GLFW_FLOATING,     windowSettings.Floating);
        glfwWindowHint(GLFW_VISIBLE,      windowSettings.Visible);
        glfwWindowHint(GLFW_AUTO_ICONIFY, windowSettings.AutoIconify);
        glfwWindowHint(GLFW_REFRESH_RATE, windowSettings.RefreshRate);
        glfwWindowHint(GLFW_SAMPLES,      windowSettings.Samples);

        m_window = glfwCreateWindow(m_settings.Size.x, m_settings.Size.y, "Engine", selectedMonitor, nullptr);

        if (!m_window)
            throw std::runtime_error("Failed to create GLFW window");

        if (m_settings.Position == glm::i32vec2(-1))
            glfwGetWindowPos(m_window, &m_settings.Position.x, &m_settings.Position.y);
        else
            glfwSetWindowPos(m_window, m_settings.Position.x, m_settings.Position.y);

        glfwSetWindowSizeLimits(m_window, m_settings.MinimumSize.x, m_settings.MinimumSize.y,
                m_settings.MaximumSize.x, m_settings.MaximumSize.y);

        if (m_settings.Fullscreen)
            SetFullscreen(true);

        glfwSetWindowUserPointer(m_window, this);
        glfwMakeContextCurrent(m_window);
    }

    void GLFW::bindKeyCallback() const
    {
        auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                    current->m_inputManager->KeyPressedEvent.Invoke(static_cast<Inputs::EKey>(key));

                if (action == GLFW_RELEASE)
                    current->m_inputManager->KeyReleasedEvent.Invoke(static_cast<Inputs::EKey>(key));
            }
        };

        glfwSetKeyCallback(m_window, keyCallback);
    }

    void GLFW::bindMouseCallback() const
    {
        auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                    current->m_inputManager->MouseButtonPressedEvent.Invoke(static_cast<Inputs::EMouseButton>(button));

                if (action == GLFW_RELEASE)
                    current->m_inputManager->MouseButtonReleasedEvent.Invoke(static_cast<Inputs::EMouseButton>(button));
            }
        };

        glfwSetMouseButtonCallback(m_window, mouseCallback);
    }

    void GLFW::bindCursorMoveCallback() const
    {
        auto cursorMoveCallback = [](GLFWwindow* window, double x, double y)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->m_inputManager->CursorMoveEvent.Invoke(glm::dvec2(x, y));
        };

        glfwSetCursorPosCallback(m_window, cursorMoveCallback);
    }

    void GLFW::bindResizeCallback() const
    {
        auto resizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->ResizeEvent.Invoke(glm::i32vec2(width, height));
        };

        glfwSetWindowSizeCallback(m_window, resizeCallback);
    }

    void GLFW::bindFramebufferResizeCallback() const
    {
        auto framebufferResizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->FramebufferResizeEvent.Invoke(glm::i32vec2(width, height));
        };

        glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
    }

    void GLFW::bindMoveCallback() const
    {
        auto moveCallback = [](GLFWwindow* window, int x, int y)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->MoveEvent.Invoke(glm::i32vec2(x, y));
        };

        glfwSetWindowPosCallback(m_window, moveCallback);
    }

    void GLFW::bindIconifyCallback() const
    {
        auto iconifyCallback = [](GLFWwindow* window, int iconified)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (iconified == GLFW_TRUE)
                    current->MinimizeEvent.Invoke();

                if (iconified == GLFW_FALSE)
                    current->MaximizeEvent.Invoke();
            }
        };

        glfwSetWindowIconifyCallback(m_window, iconifyCallback);
    }

    void GLFW::bindFocusCallback() const
    {
        auto focusCallback = [](GLFWwindow* window, int focused)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (focused == GLFW_TRUE)
                    current->GainFocusEvent.Invoke();

                if (focused == GLFW_FALSE)
                    current->LostFocusEvent.Invoke();
            }
        };

        glfwSetWindowFocusCallback(m_window, focusCallback);
    }

    void GLFW::bindCloseCallback() const
    {
        auto closeCallback = [](GLFWwindow* window)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->CloseEvent.Invoke();
        };

        glfwSetWindowCloseCallback(m_window, closeCallback);
    }

    void GLFW::CloseWindow()
    {
        ResizeEvent.RemoveAllListeners();
        MoveEvent.RemoveAllListeners();
        FramebufferResizeEvent.RemoveAllListeners();

        MinimizeEvent.RemoveAllListeners();
        MaximizeEvent.RemoveAllListeners();
        RestoreEvent.RemoveAllListeners();
        LostFocusEvent.RemoveAllListeners();
        GainFocusEvent.RemoveAllListeners();
        CloseEvent.RemoveAllListeners();

        if (m_window)
        {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }
    }

    Inputs::InputManager& Windows::GLFW::getInputManager() const
    {
        if (!m_inputManager)
            throw std::runtime_error("Input Manager Destroyed");

        return *m_inputManager.get();
    }

    void GLFW::SetMinimumSize(glm::i32vec2 size)
    {
        m_settings.MinimumSize = size;
        glfwSetWindowSizeLimits(m_window,
            m_settings.MinimumSize.x, m_settings.MinimumSize.y,
            m_settings.MaximumSize.x, m_settings.MaximumSize.y);
    }

    void GLFW::SetMaximumSize(glm::i32vec2 size)
    {
        m_settings.MaximumSize = size;
        glfwSetWindowSizeLimits(m_window,
            m_settings.MinimumSize.x, m_settings.MinimumSize.y,
            m_settings.MaximumSize.x, m_settings.MaximumSize.y);
    }

    void GLFW::SetFullscreen(bool value)
    {
        if (value)
        {
            m_fullscreen = true;

            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            glfwSetWindowMonitor
            (
                m_window,
                value ? glfwGetPrimaryMonitor() : nullptr,
                m_settings.Position.x,
                m_settings.Position.y,
                mode->width,
                mode->height,
                m_settings.RefreshRate
            );
        }
        else
        {
            m_fullscreen = true;

            glfwSetWindowMonitor
            (
                m_window,
                value ? glfwGetPrimaryMonitor() : nullptr,
                m_settings.Position.x,
                m_settings.Position.y,
                m_settings.Size.x,
                m_settings.Size.y,
                m_settings.RefreshRate
            );
        }
    }

    void GLFW::SetTitle(const std::string& title)
    {
        m_settings.Title = title;
        glfwSetWindowTitle(m_window, title.c_str());
    }

    void GLFW::SetVsync(bool vsync)
    {
        m_vsync = vsync;
        glfwSwapInterval(vsync ? 1 : 0);
    }

    glm::i32vec2 GLFW::GetSize() const
    {
        glm::i32vec2 size(-1);
        glfwGetWindowSize(m_window, &size.x, &size.y);
        return size;
    }

    glm::i32vec2 GLFW::GetPosition() const
    {
        glm::i32vec2 pos(-1);
        glfwGetWindowPos(m_window, &pos.x, &pos.y);
        return pos;
    }

    glm::i32vec2 GLFW::GetFramebufferSize() const
    {
        glm::i32vec2 size(-1);
        glfwGetFramebufferSize(m_window, &size.x, &size.y);
        return size;
    }
}