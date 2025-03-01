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

using UIPlotLines   = Engine::UI::Widgets::Plots::PlotLines;
using UIText        = Engine::UI::Widgets::Texts::Text;
using UITextPtr     = std::shared_ptr<UIText>;
using UITreeNode    = Engine::UI::Widgets::Layouts::TreeNode;
using UITreeNodePtr = std::shared_ptr<UITreeNode>;

namespace Engine::HardwareInfo
{
    ProfilerPanel::ProfilerPanel()
        : UI::Panels::WindowPanel("Profiler")
    {
        m_initHardwareInfoThread = std::thread(&ProfilerPanel::initHardwareInfo, this);
        m_calculateHardwareInfoThread = std::thread(&ProfilerPanel::calculateHardwareInfo, this);

        m_cpuUsagePlot = CreateWidget<UIPlotLines>("CPU Usage %", "", 50,
            0.0f, 100.0f, glm::vec2(0.0f, 75.0f));

        m_ramUsagePlot = CreateWidget<UIPlotLines>("RAM Usage %", "", 50,
            0.0f, 100.0f, glm::vec2(0.0f, 75.0f));

        m_gpuUsagePlot = CreateWidget<UIPlotLines>("GPU Usage %", "", 50,
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
            m_cpuInfoTree = CreateWidget<UITreeNode>("CPU Info");

            CPUInfo& info = cpuInfo.value();

            m_cpuInfoTree->CreateWidget<UIText>("Name: "                         + info.Name);
            m_cpuInfoTree->CreateWidget<UIText>("Max Clock Speed: "              + std::to_string(info.MaxClockSpeed) + "MHz");
            m_cpuInfoTree->CreateWidget<UIText>("Current Clock Speed: "          + std::to_string(info.CurrentClockSpeed) + " MHz");
            m_cpuInfoTree->CreateWidget<UIText>("L2 Cache Size: "                + std::to_string(info.L2CacheSize / 1024) + " KB");
            m_cpuInfoTree->CreateWidget<UIText>("L3 Cache Size: "                + std::to_string(info.L3CacheSize / 1024) + " KB");
            m_cpuInfoTree->CreateWidget<UIText>("Number Of Cores: "              + std::to_string(info.NumberOfCores));
            m_cpuInfoTree->CreateWidget<UIText>("Number Of Enabled Core: "       + std::to_string(info.NumberOfEnabledCore));
            m_cpuInfoTree->CreateWidget<UIText>("Number Of Logical Processors: " + std::to_string(info.NumberOfLogicalProcessors));
            m_cpuInfoTree->CreateWidget<UIText>("Thread Count: "                 + std::to_string(info.ThreadCount));
            m_cpuInfoTree->CreateWidget<UIText>("Address Width: "                + std::to_string(info.AddressWidth));

            std::string text = "Virtualization Firmware Enabled: ";
            text += info.VirtualizationFirmwareEnabled ? "True" : "False";
            m_cpuInfoTree->CreateWidget<UIText>(text);

            text = "VM Monitor Mode Extensions: ";
            text += info.VMMonitorModeExtensions ? "True" : "False";
            m_cpuInfoTree->CreateWidget<UIText>(text);
        }
        else
            LOG_ERROR("Can't get CPU Info")

        std::optional<std::list<GPUInfo>> gpuInfo = HardwareInfo::WMIWrapper::GetGPUInfo();

        if (gpuInfo.has_value())
        {
            m_gpuInfoTree = CreateWidget<UITreeNode>("GPU Info");

            int counter = 0;
            for (GPUInfo& info : gpuInfo.value())
            {
                ++counter;
                UITreeNodePtr gpuTree = m_gpuInfoTree->CreateWidget<UITreeNode>("GPU " + std::to_string(counter));

                gpuTree->CreateWidget<UIText>("Name: "                          + info.Name);
                gpuTree->CreateWidget<UIText>("Device ID: "                     + info.DeviceID);
                gpuTree->CreateWidget<UIText>("Driver Version: "                + info.DriverVersion);
                gpuTree->CreateWidget<UIText>("Current Horizontal Resolution: " + std::to_string(info.CurrentHorizontalResolution));
                gpuTree->CreateWidget<UIText>("Current Vertical Resolution: "   + std::to_string(info.CurrentVerticalResolution));
                gpuTree->CreateWidget<UIText>("CurrentRefreshRate: "            + std::to_string(info.CurrentRefreshRate));
                gpuTree->CreateWidget<UIText>("Max Refresh Rate: "              + std::to_string(info.MaxRefreshRate));
                gpuTree->CreateWidget<UIText>("Min Refresh Rate: "              + std::to_string(info.MinRefreshRate));
                gpuTree->CreateWidget<UIText>("Current Bits Per Pixel: "        + std::to_string(info.CurrentBitsPerPixel));
                gpuTree->CreateWidget<UIText>("Current Number Of Colors: "      + info.CurrentNumberOfColors);

                std::string text = "Monochrome: ";
                text += info.Monochrome ? "True" : "False";
                gpuTree->CreateWidget<UIText>(text);

                gpuTree->CreateWidget<UIText>("Installed Display Drivers: " + info.InstalledDisplayDrivers);
                gpuTree->CreateWidget<UIText>("PNP Device ID: " + info.PNPDeviceID);
            }
        }
        else
            LOG_ERROR("Can't get GPU Info")

        std::optional<std::list<RAMInfo>> ramInfo = HardwareInfo::WMIWrapper::GetRAMInfo();

        if (ramInfo.has_value())
        {
            m_ramInfoTree = CreateWidget<UITreeNode>("RAM Info");

            int counter = 0;
            for (RAMInfo& info : ramInfo.value())
            {
                ++counter;
                UITreeNodePtr ramTree = m_ramInfoTree->CreateWidget<UITreeNode>("RAM " + std::to_string(counter));

                ramTree->CreateWidget<UIText>("Manufacturer: "           + info.Manufacturer);
                ramTree->CreateWidget<UIText>("Part Number: "            + info.PartNumber);
                ramTree->CreateWidget<UIText>("Device Locator: "         + info.DeviceLocator);
                ramTree->CreateWidget<UIText>("Capacity: "               + info.Capacity + " KB");
                ramTree->CreateWidget<UIText>("Speed: "                  + std::to_string(info.Speed));
                ramTree->CreateWidget<UIText>("Configured Clock Speed: " + std::to_string(info.ConfiguredClockSpeed));
                ramTree->CreateWidget<UIText>("Configured Voltage: "     + std::to_string(info.ConfiguredVoltage) + " V");
                ramTree->CreateWidget<UIText>("Min Voltage: "            + std::to_string(info.MinVoltage) + " V");
                ramTree->CreateWidget<UIText>("Max Voltage: "            + std::to_string(info.MaxVoltage) + " V");
            }
        }
        else
            LOG_ERROR("Can't get RAM Info")
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
                m_cpuUsagePlot->SetLabel("CPU Usage: " + std::to_string(static_cast<int>(cpuLoad * 100.0f)) + "%");

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
