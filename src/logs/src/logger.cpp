#include "logs/logger.hpp"
#include "tools/time/date.hpp"

#include <iostream>

namespace Engine::Logs
{
    const std::string Logger::DEFAULT = "\033[0m";
    const std::string Logger::CYAN    = "\033[36m";
    const std::string Logger::YELLOW  = "\033[33m";
    const std::string Logger::RED     = "\033[31m";

    void Logger::PrintLog(const std::string& message, ELogLevel logLevel)
    {
        std::cout << getLogLevelOutput(logLevel)
                  << "[" << Tools::Time::Date::GetDateAndTime() << "] "
                  << message << DEFAULT << std::endl;
    }

    std::string Logger::getLogLevelOutput(ELogLevel logLevel)
    {
        switch (logLevel)
        {
            case ELogLevel::Default: return "";
            case ELogLevel::Info:    return CYAN + "[Info] ";
            case ELogLevel::Warning: return YELLOW + "[Warning] ";
            case ELogLevel::Error:   return RED + "[Error] ";
            default:                 return "[Uknown] ";
        }

        return "[Unknown] ";
    }
}
