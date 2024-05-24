#pragma once
#ifndef ENGINE_TOOLS_TIME_DATE_HPP_
#define ENGINE_TOOLS_TIME_DATE_HPP_

#include <chrono>
#include <ctime>
#include <string>

namespace Engine::Tools::Time
{
    class Date
    {
    public:
        Date() = delete;

        static inline std::string GetDate()
        {
            std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm* time = std::localtime(&now);

            std::string day = std::to_string(time->tm_mday);

            if (day.size() < 2)
                day = "0" + day;

            std::string mon = std::to_string(1 + time->tm_mon);

            if (mon.size() < 2)
                mon = "0" + mon;

            std::string year = std::to_string(1900 + time->tm_year);

            return day + "-" + mon + "-" + year;
        }

        static inline std::string GetTime()
        {
            std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm* time = std::localtime(&now);

            std::string hour = std::to_string(time->tm_hour);

            if (hour.size() < 2)
                hour = "0" + hour;

            std::string min = std::to_string(time->tm_min);

            if (min.size() < 2)
                min = "0" + min;

            std::string sec = std::to_string(time->tm_sec);

            if (sec.size() < 2)
                sec = "0" + sec;

            return hour + ":" + min + ":" + sec;
        }

        static inline std::string GetDateAndTime()
        {
            return GetDate() + " " + GetTime();
        }
    };
}

#endif // ENGINE_TOOLS_TIME_DATE_HPP_
