#pragma once
#ifndef ENGINE_APPLICATION_HPP_
#define ENGINE_APPLICATION_HPP_

#include <filesystem>

namespace Engine
{
    class Application
    {
    public:
        Application(const std::filesystem::path& projectPath);
        ~Application();

        Application(const Application& other)             = delete;
        Application(Application&& other)                  = delete;
        Application& operator=(const Application& other)  = delete;
        Application& operator=(const Application&& other) = delete;

        void Run();
        bool IsRunning() const;

        const std::filesystem::path ProjectPath;
        const std::filesystem::path ProjectShadersPath;
    };
}

#endif // ENGINE_APPLICATION_HPP_
