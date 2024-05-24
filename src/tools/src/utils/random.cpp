#include "tools/utils/random.hpp"

namespace Utils = Engine::Tools::Utils;

std::default_random_engine Utils::Random::m_generator;

int Utils::Random::GetInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_generator);
}

float Utils::Random::GetFloat(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(m_generator);
}
