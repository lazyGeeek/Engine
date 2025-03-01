#include "logs/logger.hpp"
#include "tools/time/date.hpp"

#include <cstdarg>
#include <iostream>
#include <string>

namespace Engine::Logs
{
    const std::string Logger::DEBUG   = "\033[0m";
    const std::string Logger::CYAN    = "\033[36m";
    const std::string Logger::YELLOW  = "\033[33m";
    const std::string Logger::RED     = "\033[31m";

    void Logger::Debug(char const* const format, ...)
    {
        va_list args;
        va_start(args, format);

        std::string message = parseArgs(format, args);

        va_end(args);

        printLog(message, ELogLevel::Debug);
        LogMessageReceived.Invoke(ELogLevel::Debug, message);
    }

    void Logger::Info(char const* const format, ...) {
        va_list args;
        va_start(args, format);

        std::string message = parseArgs(format, args);

        va_end(args);

        printLog(message, ELogLevel::Info);
        LogMessageReceived.Invoke(ELogLevel::Info, message);
    }

    void Logger::Warning(char const* const format, ...) {
        va_list args;
        va_start(args, format);

        std::string message = parseArgs(format, args);

        va_end(args);

        printLog(message, ELogLevel::Warning);
        LogMessageReceived.Invoke(ELogLevel::Warning, message);
    }

    void Logger::Error(char const* const format, ...) {
        va_list args;
        va_start(args, format);

        std::string message = parseArgs(format, args);

        va_end(args);

        printLog(message, ELogLevel::Error);
        LogMessageReceived.Invoke(ELogLevel::Error, message);
    }

    std::string Logger::parseArgs(char const* const format, va_list args)
    {
        size_t size = vsnprintf(nullptr, 0, format, args);
        std::string buffer;
        buffer.resize(size + 1);
        vsnprintf(&buffer[0], size + 1, format, args);

        return buffer;
    }

    void Logger::printLog(const std::string& message, ELogLevel logLevel)
    {
        std::cout << getLogLevelOutput(logLevel)
                  << "[" << Tools::Time::Date::GetDateAndTime() << "] "
                  << message << DEBUG << std::endl;
    }

    std::string Logger::getLogLevelOutput(ELogLevel logLevel)
    {
        switch (logLevel)
        {
            case ELogLevel::Debug:   return "";
            case ELogLevel::Info:    return CYAN +   "[Info] ";
            case ELogLevel::Warning: return YELLOW + "[Warning] ";
            case ELogLevel::Error:   return RED +    "[Error] ";
            default:                 return "[Uknown] ";
        }

        return "[Unknown] ";
    }
}
