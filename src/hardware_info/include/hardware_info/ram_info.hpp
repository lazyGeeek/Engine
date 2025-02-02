#pragma once
#ifndef ENGINE_HARDWARE_INFO_RAM_INFO_HPP_
#define ENGINE_HARDWARE_INFO_RAM_INFO_HPP_

#include <string>

namespace Engine::HardwareInfo
{
    struct RAMInfo
    {
        // https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/win32-physicalmemory

        std::string BankLabel            = "";
        std::string Capacity             = "";
        std::string Caption              = "";
        std::string CreationClassName    = "";
        std::string Description          = "";
        std::string DeviceLocator        = "";
        std::string Manufacturer         = "";
        std::string Model                = "";
        std::string Name                 = "";
        std::string OtherIdentifyingInfo = "";
        std::string PartNumber           = "";
        std::string SerialNumber         = "";
        std::string SKU                  = "";
        std::string Status               = "";
        std::string Tag                  = "";
        std::string Version              = "";

        uint32_t Attributes           = 0;
        uint32_t ConfiguredClockSpeed = 0;
        uint32_t ConfiguredVoltage    = 0;
        uint32_t DataWidth            = 0;
        uint32_t FormFactor           = 0;
        uint32_t InterleaveDataDepth  = 0;
        uint32_t InterleavePosition   = 0;
        uint32_t MaxVoltage           = 0;
        uint32_t MemoryType           = 0;
        uint32_t MinVoltage           = 0;
        uint32_t PositionInRow        = 0;
        uint32_t SMBIOSMemoryType     = 0;
        uint32_t Speed                = 0;
        uint32_t TotalWidth           = 0;
        uint32_t TypeDetail           = 0;

        bool HotSwappable = false;
        bool PoweredOn    = false;
        bool Removable    = false;
        bool Replaceable  = false;
    };
}

#endif // ENGINE_HARDWARE_INFO_RAM_INFO_HPP_
