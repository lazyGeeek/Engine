#pragma once
#ifndef ENGINE_LOGS_LOGGER_HPP_
#define ENGINE_LOGS_LOGGER_HPP_

#include <string>

#include "log_level.hpp"

namespace Engine::Logs
{
    class Logger
    {
    public:
        Logger() = delete;

        Logger(const Logger& other)             = delete;
        Logger(Logger&& other)                  = delete;
        Logger& operator=(const Logger& other)  = delete;
        Logger& operator=(const Logger&& other) = delete;

        static void PrintLog(const std::string& message, ELogLevel logLevel);

    private:
        static std::string getLogLevelOutput(ELogLevel logLevel = ELogLevel::Default);

        static const std::string DEFAULT;
        static const std::string RED;
        static const std::string YELLOW;
        static const std::string CYAN;
    };
}

#endif // ENGINE_LOGS_LOGGER_HPP_
