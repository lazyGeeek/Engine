#include "hardware_info/profiler_panel.hpp"
#include "hardware_info/cpu_info.hpp"

#include "logs/logger.hpp"

#include "ui/widgets/layouts/tree_node.hpp"
#include "ui/widgets/plots/plot_lines.hpp"
#include "ui/widgets/texts/text.hpp"

#include "hardware_info/wmi_wrapper.hpp"

#include <chrono>

#include <nvapi/nvapi.h>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::duration<float, std::milli> Duration;

namespace Engine::HardwareInfo
{
    ProfilerPanel::ProfilerPanel()
        : UI::Panels::WindowPanel("Profiler")
    {
        m_initHardwareInfoThread = std::thread(&ProfilerPanel::initHardwareInfo, this);
        m_calculateHardwareInfoThread = std::thread(&ProfilerPanel::calculateHardwareInfo, this);

        m_cpuUsagePlot = CreateWidget<UI::Widgets::Plots::PlotLines>("CPU Usage %", "", 50,
            0.0f, 100.0f, glm::vec2(0.0f, 75.0f));

        m_ramUsagePlot = CreateWidget<UI::Widgets::Plots::PlotLines>("RAM Usage %", "", 50,
            0.0f, 100.0f, glm::vec2(0.0f, 75.0f));

        m_gpuUsagePlot = CreateWidget<UI::Widgets::Plots::PlotLines>("GPU Usage %", "", 50,
            0.0f, 100.0f, glm::vec2(0.0f, 75.0f));
    }

    ProfilerPanel::~ProfilerPanel()
    {
        m_isThreadStop = true;
        m_calculateHardwareInfoThread.join();
        m_initHardwareInfoThread.join();

        if (m_cpuInfoTree)
            m_cpuInfoTree->RemoveAllWidgets();

        if (m_gpuInfoTree)
            m_gpuInfoTree->RemoveAllWidgets();

        if (m_ramInfoTree)
            m_ramInfoTree->RemoveAllWidgets();

        RemoveAllWidgets();
    }

    void ProfilerPanel::initHardwareInfo()
    {
        std::optional<CPUInfo> cpuInfo = HardwareInfo::WMIWrapper::GetCPUInfo();

        if (cpuInfo.has_value())
        {
            m_cpuInfoTree = CreateWidget<UI::Widgets::Layouts::TreeNode>("CPU Info");

            CPUInfo& info = cpuInfo.value();

            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Name: " + info.Name);
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Max Clock Speed: " + std::to_string(info.MaxClockSpeed) + "MHz");
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Current Clock Speed: " + std::to_string(info.CurrentClockSpeed) + " MHz");
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("L2 Cache Size: " + std::to_string(info.L2CacheSize / 1024) + " KB");
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("L3 Cache Size: " + std::to_string(info.L3CacheSize / 1024) + " KB");
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Number Of Cores: " + std::to_string(info.NumberOfCores));
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Number Of Enabled Core: " + std::to_string(info.NumberOfEnabledCore));
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Number Of Logical Processors: " + std::to_string(info.NumberOfLogicalProcessors));
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Thread Count: " + std::to_string(info.ThreadCount));
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>("Address Width: " + std::to_string(info.AddressWidth));

            std::string text = "Virtualization Firmware Enabled: ";
            text += info.VirtualizationFirmwareEnabled ? "True" : "False";
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>(text);

            text = "VM Monitor Mode Extensions: ";
            text += info.VMMonitorModeExtensions ? "True" : "False";
            m_cpuInfoTree->CreateWidget<UI::Widgets::Texts::Text>(text);
        }
        else
            Logs::Logger::PrintLog("Can't get CPU Info", Logs::ELogLevel::Error);

        std::optional<std::list<GPUInfo>> gpuInfo = HardwareInfo::WMIWrapper::GetGPUInfo();

        if (gpuInfo.has_value())
        {
            m_gpuInfoTree = CreateWidget<UI::Widgets::Layouts::TreeNode>("GPU Info");

            int counter = 0;
            for (GPUInfo& info : gpuInfo.value())
            {
                ++counter;
                std::shared_ptr<UI::Widgets::Layouts::TreeNode> gpuTree = m_gpuInfoTree->CreateWidget<UI::Widgets::Layouts::TreeNode>("GPU " + std::to_string(counter));

                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Name: " + info.Name);
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Device ID: " + info.DeviceID);
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Driver Version: " + info.DriverVersion);
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Current Horizontal Resolution: " + std::to_string(info.CurrentHorizontalResolution));
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Current Vertical Resolution: " + std::to_string(info.CurrentVerticalResolution));
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("CurrentRefreshRate: " + std::to_string(info.CurrentRefreshRate));
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Max Refresh Rate: " + std::to_string(info.MaxRefreshRate));
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Min Refresh Rate: " + std::to_string(info.MinRefreshRate));
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Current Bits Per Pixel: " + std::to_string(info.CurrentBitsPerPixel));
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Current Number Of Colors: " + info.CurrentNumberOfColors);

                std::string text = "Monochrome: ";
                text += info.Monochrome ? "True" : "False";
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>(text);

                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("Installed Display Drivers: " + info.InstalledDisplayDrivers);
                gpuTree->CreateWidget<UI::Widgets::Texts::Text>("PNP Device ID: " + info.PNPDeviceID);
            }
        }
        else
            Logs::Logger::PrintLog("Can't get GPU Info", Logs::ELogLevel::Error);

        std::optional<std::list<RAMInfo>> ramInfo = HardwareInfo::WMIWrapper::GetRAMInfo();

        if (ramInfo.has_value())
        {
            m_ramInfoTree = CreateWidget<UI::Widgets::Layouts::TreeNode>("RAM Info");

            int counter = 0;
            for (RAMInfo& info : ramInfo.value())
            {
                ++counter;
                std::shared_ptr<UI::Widgets::Layouts::TreeNode> ramTree = m_ramInfoTree->CreateWidget<UI::Widgets::Layouts::TreeNode>("RAM " + std::to_string(counter));

                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Manufacturer: " + info.Manufacturer);
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Part Number: " + info.PartNumber);
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Device Locator: " + info.DeviceLocator);
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Capacity: " + info.Capacity + " KB");
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Speed: " + std::to_string(info.Speed));
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Configured Clock Speed: " + std::to_string(info.ConfiguredClockSpeed));
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Configured Voltage: " + std::to_string(info.ConfiguredVoltage) + " V");
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Min Voltage: " + std::to_string(info.MinVoltage) + " V");
                ramTree->CreateWidget<UI::Widgets::Texts::Text>("Max Voltage: " + std::to_string(info.MaxVoltage) + " V");
            }
        }
        else
            Logs::Logger::PrintLog("Can't get RAM Info", Logs::ELogLevel::Error);
    }

    void ProfilerPanel::calculateHardwareInfo()
    {
        float timer = 0.0f;
        Clock::time_point currentFrame = Clock::now();
        Clock::time_point lastFrame = currentFrame;

        NV_GPU_DYNAMIC_PSTATES_INFO_EX pStatesInfo;
        pStatesInfo.version = NV_GPU_DYNAMIC_PSTATES_INFO_EX_VER;

        std::vector<NvPhysicalGpuHandle> physicalGpuHandles(NVAPI_MAX_PHYSICAL_GPUS);
        NvU32 physicalGpuCount;
        NvAPI_EnumPhysicalGPUs(physicalGpuHandles.data(), &physicalGpuCount);

        while (!m_isThreadStop)
        {
            currentFrame = Clock::now();
            timer += std::chrono::duration_cast<Duration>(currentFrame - lastFrame).count();

            // Update data every 250.0f milliseconds
            if (timer > 250.0f)
            {
                FILETIME idleTime, kernelTime, userTime;
                float cpuLoad = GetSystemTimes(&idleTime, &kernelTime, &userTime) ?
                    calculateCPULoad(fileTimeToInt64(idleTime), fileTimeToInt64(kernelTime) + fileTimeToInt64(userTime)) : 0.0f;

                m_cpuUsagePlot->AddSample(cpuLoad * 100.0f);
                m_cpuUsagePlot->SetLabel("RAM Usage: " + std::to_string(static_cast<int>(cpuLoad * 100.0f)) + "%");

                MEMORYSTATUSEX memInfo;
                memInfo.dwLength = sizeof(MEMORYSTATUSEX);
                GlobalMemoryStatusEx(&memInfo);

                DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
                DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

                float ramUsage = (physMemUsed * 100.0f) / totalPhysMem;
                m_ramUsagePlot->AddSample(ramUsage);
                m_ramUsagePlot->SetLabel("RAM Usage: " + std::to_string(static_cast<int>(ramUsage)) + "%");

                if (NvAPI_GPU_GetDynamicPstatesInfoEx(physicalGpuHandles[0], &pStatesInfo) == NVAPI_OK)
                {
                    if (pStatesInfo.utilization[0].bIsPresent)
                    {
                        NvU32 gpuUsage = pStatesInfo.utilization[0].percentage;
                        m_gpuUsagePlot->AddSample(gpuUsage);
                        m_gpuUsagePlot->SetLabel("GPU Usage: " + std::to_string(gpuUsage) + "%");
                    }
                }

                timer = 0.0f;
            }

            lastFrame = currentFrame;
        }
    }

    float ProfilerPanel::calculateCPULoad(uint64_t idleTicks, uint64_t totalTicks)
    {
        uint64_t totalTicksSinceLastTime = totalTicks - m_cpuPreviousTotalTicks;
        uint64_t idleTicksSinceLastTime = idleTicks - m_cpuPreviousIdleTicks;

        float ret = 1.0f - ((totalTicksSinceLastTime > 0) ?
            (static_cast<float>(idleTicksSinceLastTime) / totalTicksSinceLastTime) : 0.0f);

        m_cpuPreviousTotalTicks = totalTicks;
        m_cpuPreviousIdleTicks  = idleTicks;

        return ret;
    }

    uint64_t ProfilerPanel::fileTimeToInt64(const FILETIME& ft)
    {
        return (static_cast<uint64_t>(ft.dwHighDateTime) << 32) | (static_cast<uint64_t>(ft.dwLowDateTime));
    }
}
