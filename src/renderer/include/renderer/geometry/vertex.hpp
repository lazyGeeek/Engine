#pragma once
#ifndef ENGINE_RENDERER_GEOMETRY_VERTEX_HPP_
#define ENGINE_RENDERER_GEOMETRY_VERTEX_HPP_

#include <array>

namespace Engine::Renderer::Geometry
{
    struct Vertex
    {
        std::array<float, 3> Position;
        std::array<float, 2> TexCoords;
        std::array<float, 3> Normals;
        std::array<float, 3> Tangent;
        std::array<float, 3> Bitangent;
    };
}

#endif // ENGINE_RENDERER_GEOMETRY_VERTEX_HPP_
