#pragma once
#ifndef ENGINE_HARDWARE_INFO_GPU_INFO_HPP_
#define ENGINE_HARDWARE_INFO_GPU_INFO_HPP_

#include <string>

namespace Engine::HardwareInfo
{
    struct GPUInfo
    {
        // https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/win32-videocontroller

        std::string AdapterCompatibility    = "";
        std::string AdapterDACType          = "";
        std::string Caption                 = "";
        std::string CurrentNumberOfColors   = "";
        std::string CreationClassName       = "";
        std::string Description             = "";
        std::string DeviceID                = "";
        std::string DriverVersion           = "";
        std::string ErrorDescription        = "";
        std::string InfFilename             = "";
        std::string InfSection              = "";
        std::string InstalledDisplayDrivers = "";
        std::string Name                    = "";
        std::string PNPDeviceID             = "";
        std::string Status                  = "";
        std::string SystemCreationClassName = "";
        std::string SystemName              = "";
        std::string VideoModeDescription    = "";
        std::string VideoProcessor          = "";

        uint32_t AdapterRAM                   = 0;
        uint32_t Availability                 = 0;
        uint32_t ColorTableEntries            = 0;
        uint32_t ConfigManagerErrorCode       = 0;
        uint32_t CurrentBitsPerPixel          = 0;
        uint32_t CurrentHorizontalResolution  = 0;
        uint32_t CurrentNumberOfColumns       = 0;
        uint32_t CurrentNumberOfRows          = 0;
        uint32_t CurrentRefreshRate           = 0;
        uint32_t CurrentScanMode              = 0;
        uint32_t CurrentVerticalResolution    = 0;
        uint32_t DitherType                   = 0;
        uint32_t DeviceSpecificPens           = 0;
        uint32_t ICMIntent                    = 0;
        uint32_t ICMMethod                    = 0;
        uint32_t LastErrorCode                = 0;
        uint32_t MaxMemorySupported           = 0;
        uint32_t MaxNumberControlled          = 0;
        uint32_t MaxRefreshRate               = 0;
        uint32_t MinRefreshRate               = 0;
        uint32_t NumberOfColorPlanes          = 0;
        uint32_t NumberOfVideoPages           = 0;
        uint32_t ProtocolSupported            = 0;
        uint32_t ReservedSystemPaletteEntries = 0;
        uint32_t SpecificationVersion         = 0;
        uint32_t StatusInfo                   = 0;
        uint32_t SystemPaletteEntries         = 0;
        uint32_t VideoArchitecture            = 0;
        uint32_t VideoMemoryType              = 0;
        uint32_t VideoMode                    = 0;

        bool ConfigManagerUserConfig  = false;
        bool ErrorCleared             = false;
        bool Monochrome               = false;
        bool PowerManagementSupported = false;
    };
}

#endif // ENGINE_HARDWARE_INFO_GPU_INFO_HPP_
