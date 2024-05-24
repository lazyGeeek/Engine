#pragma once
#ifndef ENGINE_TOOLS_UTILS_RANDOM_HPP_
#define ENGINE_TOOLS_UTILS_RANDOM_HPP_

#include <random>

namespace Engine::Tools::Utils
{
    class Random
    {
    public:
        Random() = delete;

        static int GetInt(int min, int max);
        static float GetFloat(float min, float max);

    private:
        static std::default_random_engine m_generator;
    };
}

#endif // ENGINE_TOOLS_UTILS_RANDOM_HPP_
