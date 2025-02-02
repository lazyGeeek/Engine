#pragma once
#ifndef ENGINE_HARDWARE_INFO_PROFILER_PANEL_HPP_
#define ENGINE_HARDWARE_INFO_PROFILER_PANEL_HPP_

#include <thread>
#include <memory>
#include <windows.h>

#include "ui/panels/window_panel.hpp"

namespace Engine::UI::Widgets::Layouts { class TreeNode; }
namespace Engine::UI::Widgets::Plots   { class PlotLines; }

namespace Engine::HardwareInfo
{
    class ProfilerPanel : public UI::Panels::WindowPanel
    {
    public:
        ProfilerPanel();
        ~ProfilerPanel();

        ProfilerPanel(const ProfilerPanel& other)             = delete;
        ProfilerPanel(ProfilerPanel&& other)                  = delete;
        ProfilerPanel& operator=(const ProfilerPanel& other)  = delete;
        ProfilerPanel& operator=(const ProfilerPanel&& other) = delete;

    private:
        void initHardwareInfo();
        void calculateHardwareInfo();
        float calculateCPULoad(uint64_t idleTicks, uint64_t totalTicks);
        uint64_t fileTimeToInt64(const FILETIME& ft);

        std::thread m_initHardwareInfoThread;
        std::thread m_calculateHardwareInfoThread;
        bool m_isThreadStop = false;

        uint64_t m_cpuPreviousTotalTicks = 0;
        uint64_t m_cpuPreviousIdleTicks  = 0;

        std::shared_ptr<UI::Widgets::Layouts::TreeNode> m_cpuInfoTree = nullptr;
        std::shared_ptr<UI::Widgets::Layouts::TreeNode> m_gpuInfoTree = nullptr;
        std::shared_ptr<UI::Widgets::Layouts::TreeNode> m_ramInfoTree = nullptr;

        std::shared_ptr<UI::Widgets::Plots::PlotLines> m_cpuUsagePlot = nullptr;
        std::shared_ptr<UI::Widgets::Plots::PlotLines> m_ramUsagePlot = nullptr;
        std::shared_ptr<UI::Widgets::Plots::PlotLines> m_gpuUsagePlot = nullptr;

    };
}

#endif // ENGINE_HARDWARE_INFO_PROFILER_PANEL_HPP_
