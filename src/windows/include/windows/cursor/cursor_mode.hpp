#pragma once
#ifndef ENGINE_WINDOWS_CURSOR_CURSOR_MODE_HPP_
#define ENGINE_WINDOWS_CURSOR_CURSOR_MODE_HPP_

#include <stdint.h>

namespace Engine::Windows::Cursor
{
    enum class ECursorMode
    {
        Normal   = 0x00034001,
        Disabled = 0x00034003,
        Hidden   = 0x00034002
    };
}

#endif // ENGINE_WINDOWS_CURSOR_CURSOR_MODE_HPP_
