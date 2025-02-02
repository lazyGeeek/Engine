#pragma once
#ifndef ENGINE_HARDWARE_INFO_WMI_WRAPPER_HPP_
#define ENGINE_HARDWARE_INFO_WMI_WRAPPER_HPP_

#include <any>
#include <list>
#include <optional>
#include <string>

#include "hardware_info/cpu_info.hpp"
#include "hardware_info/gpu_info.hpp"
#include "hardware_info/ram_info.hpp"

struct IWbemLocator;
struct IWbemServices;
struct IWbemClassObject;

namespace Engine::HardwareInfo
{
    struct WMIWrapper
    {
    public:
        static std::optional<CPUInfo> GetCPUInfo();
        static std::optional<std::list<GPUInfo>> GetGPUInfo();
        static std::optional<std::list<RAMInfo>> GetRAMInfo();

    private:
        static std::any getValue(IWbemClassObject* object, const std::wstring& value);
    };
}

#endif // ENGINE_HARDWARE_INFO_WMI_WRAPPER_HPP_
