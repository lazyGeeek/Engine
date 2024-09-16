#pragma once
#ifndef ENGINE_RENDERER_DRIVER_HPP_
#define ENGINE_RENDERER_DRIVER_HPP_

#include "tools/services/service_interface.hpp"

namespace Engine::Renderer
{
    class Driver : public Tools::Services::IService
    {
    public:
        Driver(bool debug = false);
        virtual ~Driver() = default;

        Driver(const Driver& other)             = delete;
        Driver(Driver&& other)                  = delete;
        Driver& operator=(const Driver& other)  = delete;
        Driver& operator=(const Driver&& other) = delete;

        //bool IsActive() const { return m_isActive; }

    private:
        static void __stdcall GLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam);
        void initGlew();

        //bool m_isActive = false;

    };
}

#endif // ENGINE_RENDERER_DRIVER_HPP_
