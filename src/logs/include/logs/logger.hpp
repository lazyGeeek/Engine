#pragma once
#ifndef ENGINE_LOGS_LOGGER_HPP_
#define ENGINE_LOGS_LOGGER_HPP_

#include <string>

#include "log_level.hpp"
#include "tools/eventing/event.hpp"

#define LOG_DEBUG(format, ...)   Engine::Logs::Logger::Debug(format, __VA_ARGS__);
#define LOG_INFO(format, ...)    Engine::Logs::Logger::Info(format, __VA_ARGS__);
#define LOG_WARNING(format, ...) Engine::Logs::Logger::Warning(format, __VA_ARGS__);
#define LOG_ERROR(format, ...)   Engine::Logs::Logger::Error(format, __VA_ARGS__);

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

        static void Debug(char const* const format, ...);
        static void Info(char const* const format, ...);
        static void Warning(char const* const format, ...);
        static void Error(char const* const format, ...);

        static inline Tools::Eventing::Event<ELogLevel, const std::string&> LogMessageReceived;

    private:
        static std::string parseArgs(char const* const format, va_list args);

        static std::string getLogLevelOutput(ELogLevel logLevel = ELogLevel::Debug);
        static void printLog(const std::string& message, ELogLevel logLevel = ELogLevel::Info);

        static const std::string DEBUG;
        static const std::string RED;
        static const std::string YELLOW;
        static const std::string CYAN;
    };
}

#endif // ENGINE_LOGS_LOGGER_HPP_
