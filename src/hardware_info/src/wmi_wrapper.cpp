#include "hardware_info/wmi_wrapper.hpp"

#pragma comment(lib, "wbemuuid.lib")

#include <WbemIdl.h>
#include <comdef.h>

#include "logs/logger.hpp"

namespace Engine::HardwareInfo
{
    std::optional<CPUInfo> WMIWrapper::GetCPUInfo()
    {
        IWbemLocator* m_locator = nullptr;
        IWbemServices* m_service = nullptr;

        HRESULT res = CoInitializeSecurity(nullptr, -1, nullptr, nullptr,
            RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
            nullptr, EOAC_NONE, nullptr);

        res &= CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        res &= CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&m_locator);

        if (m_locator)
        {
            res &= m_locator->ConnectServer(_bstr_t("ROOT\\CIMV2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &m_service);

            if (m_service)
                res &= CoSetProxyBlanket(m_service, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                    RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
        }

        if (FAILED(res))
        {
            LOG_ERROR("[WMI Wrapper] Can't initialize WMI");

            if (m_locator) m_locator->Release();
            if (m_service) m_service->Release();

            CoUninitialize();

            return std::nullopt;
        }

        IEnumWbemClassObject* enumerator = nullptr;
        const std::wstring query = L"SELECT * FROM Win32_Processor";

        if (FAILED(m_service->ExecQuery(bstr_t(L"WQL"), bstr_t(query.c_str()),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &enumerator)))
        {
            LOG_ERROR("[WMI Wrapper] Can't execute query");

            if (m_locator) m_locator->Release();
            if (m_service) m_service->Release();

            CoUninitialize();

            return std::nullopt;
        }

        ULONG exit = 0;
        IWbemClassObject* object = nullptr;
        std::any value;
        CPUInfo returnCpuInfo;

        while (enumerator)
        {
            enumerator->Next(WBEM_INFINITE, 1, &object, &exit);

            if (!exit) break;

            value = getValue(object, L"AssetTag");
            returnCpuInfo.AssetTag = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Caption");
            returnCpuInfo.Caption = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"CreationClassName");
            returnCpuInfo.CreationClassName = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Description");
            returnCpuInfo.Description = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"DeviceId");
            returnCpuInfo.DeviceId = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Manufacturer");
            returnCpuInfo.Manufacturer = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Name");
            returnCpuInfo.Name = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"PartNumber");
            returnCpuInfo.PartNumber = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"ProcessorId");
            returnCpuInfo.ProcessorId = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Role");
            returnCpuInfo.Role = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SerialNumber");
            returnCpuInfo.SerialNumber = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SocketDesignation");
            returnCpuInfo.SocketDesignation = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Status");
            returnCpuInfo.Status = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SystemCreationClassName");
            returnCpuInfo.SystemCreationClassName = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SystemName");
            returnCpuInfo.SystemName = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Version");
            returnCpuInfo.Version = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"AddressWidth");
            returnCpuInfo.AddressWidth = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"Architecture");
            returnCpuInfo.Architecture = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"Characteristics");
            returnCpuInfo.Characteristics = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentClockSpeed");
            returnCpuInfo.CurrentClockSpeed = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentVoltage");
            returnCpuInfo.CurrentVoltage = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"DataWidth");
            returnCpuInfo.DataWidth = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"Family");
            returnCpuInfo.Family = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"L2CacheSize");
            returnCpuInfo.L2CacheSize = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"L2CacheSpeed");
            returnCpuInfo.L2CacheSpeed = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"L3CacheSize");
            returnCpuInfo.L3CacheSize = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"L3CacheSpeed");
            returnCpuInfo.L3CacheSpeed = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"Level");
            returnCpuInfo.Level = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"LoadPercentage");
            returnCpuInfo.LoadPercentage = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MaxClockSpeed");
            returnCpuInfo.MaxClockSpeed = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"NumberOfCores");
            returnCpuInfo.NumberOfCores = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"NumberOfEnabledCore");
            returnCpuInfo.NumberOfEnabledCore = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"NumberOfLogicalProcessors");
            returnCpuInfo.NumberOfLogicalProcessors = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ProcessorType");
            returnCpuInfo.ProcessorType = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"StatusInfo");
            returnCpuInfo.StatusInfo = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ThreadCount");
            returnCpuInfo.ThreadCount = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"VirtualizationFirmwareEnabled");
            returnCpuInfo.VirtualizationFirmwareEnabled = value.has_value() ? std::any_cast<bool>(value) : false;

            value = getValue(object, L"VMMonitorModeExtensions");
            returnCpuInfo.VMMonitorModeExtensions = value.has_value() ? std::any_cast<bool>(value) : false;
        }

        if (m_locator) m_locator->Release();
        if (m_service) m_service->Release();

        CoUninitialize();

        return returnCpuInfo;
    }

    std::optional<std::list<GPUInfo>> WMIWrapper::GetGPUInfo()
    {
        IWbemLocator* m_locator = nullptr;
        IWbemServices* m_service = nullptr;

        HRESULT res = CoInitializeSecurity(nullptr, -1, nullptr, nullptr,
            RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
            nullptr, EOAC_NONE, nullptr);

        res &= CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        res &= CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&m_locator);

        if (m_locator)
        {
            res &= m_locator->ConnectServer(_bstr_t("ROOT\\CIMV2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &m_service);

            if (m_service)
                res &= CoSetProxyBlanket(m_service, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                    RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
        }

        if (FAILED(res))
        {
            LOG_ERROR("[WMI Wrapper] Can't initialize WMI");

            if (m_locator) m_locator->Release();
            if (m_service) m_service->Release();

            CoUninitialize();

            return std::nullopt;
        }

        IEnumWbemClassObject* enumerator = nullptr;
        const std::wstring query = L"SELECT * FROM Win32_VideoController";

        if (FAILED(m_service->ExecQuery(bstr_t(L"WQL"), bstr_t(query.c_str()),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &enumerator)))
        {
            LOG_ERROR("[WMI Wrapper] Can't execute query");

            if (m_locator) m_locator->Release();
            if (m_service) m_service->Release();

            CoUninitialize();

            return std::nullopt;
        }

        ULONG exit = 0;
        IWbemClassObject* object = nullptr;
        std::any value;
        std::list<GPUInfo> returnGpuInfo;

        while (enumerator)
        {
            enumerator->Next(WBEM_INFINITE, 1, &object, &exit);

            if (!exit) break;

            GPUInfo info;

            value = getValue(object, L"AdapterCompatibility");
            info.AdapterCompatibility = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"AdapterDACType");
            info.AdapterDACType = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Caption");
            info.Caption = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"CurrentNumberOfColors");
            info.CurrentNumberOfColors = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"CreationClassName");
            info.CreationClassName = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Description");
            info.Description = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"DeviceID");
            info.DeviceID = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"DriverVersion");
            info.DriverVersion = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"ErrorDescription");
            info.ErrorDescription = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"InfFilename");
            info.InfFilename = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"InfSection");
            info.InfSection = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"InstalledDisplayDrivers");
            info.InstalledDisplayDrivers = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Name");
            info.Name = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"PNPDeviceID");
            info.PNPDeviceID = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Status");
            info.Status = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SystemCreationClassName");
            info.SystemCreationClassName = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SystemName");
            info.SystemName = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"VideoModeDescription");
            info.VideoModeDescription = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"VideoProcessor");
            info.VideoProcessor = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"AdapterRAM");
            info.AdapterRAM = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"Availability");
            info.Availability = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ColorTableEntries");
            info.ColorTableEntries = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ConfigManagerErrorCode");
            info.ConfigManagerErrorCode = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentBitsPerPixel");
            info.CurrentBitsPerPixel = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentHorizontalResolution");
            info.CurrentHorizontalResolution = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentNumberOfColumns");
            info.CurrentNumberOfColumns = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentNumberOfRows");
            info.CurrentNumberOfRows = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentRefreshRate");
            info.CurrentRefreshRate = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentScanMode");
            info.CurrentScanMode = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"CurrentVerticalResolution");
            info.CurrentVerticalResolution = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"DitherType");
            info.DitherType = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"DeviceSpecificPens");
            info.DeviceSpecificPens = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ICMIntent");
            info.ICMIntent = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ICMMethod");
            info.ICMMethod = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"LastErrorCode");
            info.LastErrorCode = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MaxMemorySupported");
            info.MaxMemorySupported = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MaxNumberControlled");
            info.MaxNumberControlled = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MaxRefreshRate");
            info.MaxRefreshRate = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MinRefreshRate");
            info.MinRefreshRate = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"NumberOfColorPlanes");
            info.NumberOfColorPlanes = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"NumberOfVideoPages");
            info.NumberOfVideoPages = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ProtocolSupported");
            info.ProtocolSupported = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ReservedSystemPaletteEntries");
            info.ReservedSystemPaletteEntries = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"SpecificationVersion");
            info.SpecificationVersion = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"StatusInfo");
            info.StatusInfo = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"SystemPaletteEntries");
            info.SystemPaletteEntries = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"VideoArchitecture");
            info.VideoArchitecture = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"VideoMemoryType");
            info.VideoMemoryType = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"VideoMode");
            info.VideoMode = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ConfigManagerUserConfig");
            info.ConfigManagerUserConfig = value.has_value() ? std::any_cast<bool>(value) : false;

            value = getValue(object, L"ErrorCleared");
            info.ErrorCleared = value.has_value() ? std::any_cast<bool>(value) : false;

            value = getValue(object, L"Monochrome");
            info.Monochrome = value.has_value() ? std::any_cast<bool>(value) : false;

            value = getValue(object, L"PowerManagementSupported");
            info.PowerManagementSupported = value.has_value() ? std::any_cast<bool>(value) : false;

            returnGpuInfo.emplace_back(std::move(info));
        }

        if (m_locator) m_locator->Release();
        if (m_service) m_service->Release();

        CoUninitialize();

        if (returnGpuInfo.empty())
            return std::nullopt;

        return returnGpuInfo;
    }

    std::optional<std::list<RAMInfo>> WMIWrapper::GetRAMInfo()
    {
        IWbemLocator* m_locator = nullptr;
        IWbemServices* m_service = nullptr;

        HRESULT res = CoInitializeSecurity(nullptr, -1, nullptr, nullptr,
            RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
            nullptr, EOAC_NONE, nullptr);

        res &= CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        res &= CoCreateInstance(CLSID_WbemLocator, nullptr, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&m_locator);

        if (m_locator)
        {
            res &= m_locator->ConnectServer(_bstr_t("ROOT\\CIMV2"), nullptr, nullptr, nullptr, 0, nullptr, nullptr, &m_service);

            if (m_service)
                res &= CoSetProxyBlanket(m_service, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr,
                    RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
        }

        if (FAILED(res))
        {
            LOG_ERROR("[WMI Wrapper] Can't initialize WMI");

            if (m_locator) m_locator->Release();
            if (m_service) m_service->Release();

            CoUninitialize();

            return std::nullopt;
        }

        IEnumWbemClassObject* enumerator = nullptr;
        const std::wstring query = L"SELECT * FROM Win32_PhysicalMemory";

        if (FAILED(m_service->ExecQuery(bstr_t(L"WQL"), bstr_t(query.c_str()),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &enumerator)))
        {
            LOG_ERROR("[WMI Wrapper] Can't execute query");

            if (m_locator) m_locator->Release();
            if (m_service) m_service->Release();

            CoUninitialize();

            return std::nullopt;
        }

        ULONG exit = 0;
        IWbemClassObject* object = nullptr;
        std::any value;
        std::list<RAMInfo> returnRamInfo;

        while (enumerator)
        {
            enumerator->Next(WBEM_INFINITE, 1, &object, &exit);

            if (!exit) break;

            RAMInfo info;

            value = getValue(object, L"BankLabel");
            info.BankLabel = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Capacity");
            info.Capacity = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Caption");
            info.Caption = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"CreationClassName");
            info.CreationClassName = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Description");
            info.Description = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"DeviceLocator");
            info.DeviceLocator = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Manufacturer");
            info.Manufacturer = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Model");
            info.Model = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Name");
            info.Name = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"OtherIdentifyingInfo");
            info.OtherIdentifyingInfo = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"PartNumber");
            info.PartNumber = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SerialNumber");
            info.SerialNumber = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"SKU");
            info.SKU = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Status");
            info.Status = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Tag");
            info.Tag = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Version");
            info.Version = value.has_value() ? std::any_cast<std::string>(value) : "";

            value = getValue(object, L"Attributes");
            info.Attributes = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ConfiguredClockSpeed");
            info.ConfiguredClockSpeed = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"ConfiguredVoltage");
            info.ConfiguredVoltage = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"DataWidth");
            info.DataWidth = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"FormFactor");
            info.FormFactor = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"InterleaveDataDepth");
            info.InterleaveDataDepth = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"InterleavePosition");
            info.InterleavePosition = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MaxVoltage");
            info.MaxVoltage = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MemoryType");
            info.MemoryType = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"MinVoltage");
            info.MinVoltage = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"PositionInRow");
            info.PositionInRow = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"SMBIOSMemoryType");
            info.SMBIOSMemoryType = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"Speed");
            info.Speed = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"TotalWidth");
            info.TotalWidth = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"TypeDetail");
            info.TypeDetail = value.has_value() ? std::any_cast<uint32_t>(value) : 0;

            value = getValue(object, L"HotSwappable");
            info.HotSwappable = value.has_value() ? std::any_cast<bool>(value) : false;

            value = getValue(object, L"PoweredOn");
            info.PoweredOn = value.has_value() ? std::any_cast<bool>(value) : false;

            value = getValue(object, L"Removable");
            info.Removable = value.has_value() ? std::any_cast<bool>(value) : false;

            value = getValue(object, L"Replaceable");
            info.Replaceable = value.has_value() ? std::any_cast<bool>(value) : false;

            returnRamInfo.emplace_back(std::move(info));
        }

        if (m_locator) m_locator->Release();
        if (m_service) m_service->Release();

        CoUninitialize();

        if (returnRamInfo.empty())
            return std::nullopt;

        return returnRamInfo;
    }

    std::any WMIWrapper::getValue(IWbemClassObject* object, const std::wstring& value)
    {
        VARIANT variant { 0 };

        if (!SUCCEEDED(object->Get(value.c_str(), 0, &variant, nullptr, nullptr)) &&
            variant.vt != VT_EMPTY && variant.vt != VT_NULL)
            return std::any();


        if (V_VT(&variant) == VT_BSTR)
        {
            std::wstring temp = variant.bstrVal;
            int size = WideCharToMultiByte(CP_UTF8, 0, &temp[0], static_cast<int>(temp.size()), nullptr, 0, nullptr, nullptr);
            std::string result(size, 0);
            WideCharToMultiByte(CP_UTF8, 0, temp.data(), static_cast<int>(temp.size()), result.data(), size, nullptr, nullptr);
            VariantClear(&variant);
            return result;
        }
        else if (V_VT(&variant) == VT_I4)
            return static_cast<uint32_t>(variant.uiVal);
        else if (V_VT(&variant) == VT_BOOL)
            return static_cast<bool>(variant.boolVal);

        return std::any();
    }
}
