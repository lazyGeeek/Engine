#pragma once
#ifndef ENGINE_TOOLS_SERVICES_SERVICE_INTERFACE_HPP_
#define ENGINE_TOOLS_SERVICES_SERVICE_INTERFACE_HPP_

#include <typeindex>

namespace Engine::Tools::Services
{
    class IService
    {
    public:
        virtual ~IService() = default;
    };
}

#endif // ENGINE_TOOLS_SERVICES_SERVICE_INTERFACE_HPP_
