#pragma once
#ifndef ENGINE_HARDWARE_INFO_CPU_INFO_HPP_
#define ENGINE_HARDWARE_INFO_CPU_INFO_HPP_

#include <string>

namespace Engine::HardwareInfo
{
    struct CPUInfo
    {
        // https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/win32-processor

        std::string AssetTag                = "";
        std::string Caption                 = "";
        std::string CreationClassName       = "";
        std::string Description             = "";
        std::string DeviceId                = "";
        std::string Manufacturer            = "";
        std::string Name                    = "";
        std::string PartNumber              = "";
        std::string ProcessorId             = "";
        std::string Role                    = "";
        std::string SerialNumber            = "";
        std::string SocketDesignation       = "";
        std::string Status                  = "";
        std::string SystemCreationClassName = "";
        std::string SystemName              = "";
        std::string Version                 = "";

        uint32_t AddressWidth              = 0;
        uint32_t Architecture              = 0;
        uint32_t Characteristics           = 0;
        uint32_t CurrentClockSpeed         = 0;
        uint32_t CurrentVoltage            = 0;
        uint32_t DataWidth                 = 0;
        uint32_t Family                    = 0;
        uint32_t L2CacheSize               = 0;
        uint32_t L2CacheSpeed              = 0;
        uint32_t L3CacheSize               = 0;
        uint32_t L3CacheSpeed              = 0;
        uint32_t Level                     = 0;
        uint32_t LoadPercentage            = 0;
        uint32_t MaxClockSpeed             = 0;
        uint32_t NumberOfCores             = 0;
        uint32_t NumberOfEnabledCore       = 0;
        uint32_t NumberOfLogicalProcessors = 0;
        uint32_t ProcessorType             = 0;
        uint32_t StatusInfo                = 0;
        uint32_t ThreadCount               = 0;

        bool VirtualizationFirmwareEnabled = false;
        bool VMMonitorModeExtensions       = false;
    };
}

#endif // ENGINE_HARDWARE_INFO_CPU_INFO_HPP_
