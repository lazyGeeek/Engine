#pragma once
#ifndef ENGINE_TOOLS_TIME_GLOBAL_CLOCK_HPP_
#define ENGINE_TOOLS_TIME_GLOBAL_CLOCK_HPP_

#include <chrono>

#include "tools/services/service_interface.hpp"

namespace Engine::Tools::Time
{
    class GlobalClock : public Services::IService
    {
        using Microsecs = std::chrono::microseconds;
        using SteadyClock = std::chrono::steady_clock;

    public:
        GlobalClock();
        virtual ~GlobalClock() = default;

        GlobalClock(const GlobalClock& other)             = delete;
        GlobalClock(GlobalClock&& other)                  = delete;
        GlobalClock& operator=(const GlobalClock& other)  = delete;
        GlobalClock& operator=(const GlobalClock&& other) = delete;

        void Start();
        void UpdateDelta();

        double GetDeltaMS();
        double GetDurationMS();

    private:
        SteadyClock::time_point m_start;
        SteadyClock::time_point m_lastDeltaPoint;

        std::chrono::duration<double> m_delta;
    };
}

#endif // ENGINE_TOOLS_TIME_GLOBAL_CLOCK_HPP_
