#pragma once
#ifndef ENGINE_RENDERER_RESOURCES_MESH_HPP_
#define ENGINE_RENDERER_RESOURCES_MESH_HPP_

#include <filesystem>
#include <memory>
#include <vector>

#include "mesh_interface.hpp"
#include "renderer/buffers/vertex_array.hpp"

namespace Engine::Renderer::Geometry { class Vertex; }

namespace Engine::Renderer::Buffers
{
    class IndexBuffer;

    template<typename T>
    class VertexBuffer;
}

namespace Engine::Renderer::Resources
{
    class Material;

    class Mesh : public IMesh
    {
    public:
        Mesh(const std::vector<Geometry::Vertex>& vertices,
            const std::vector<uint32_t>& indices,
            const std::shared_ptr<Material>& material);
        ~Mesh();

        Mesh(const Mesh& other)             = delete;
        Mesh(Mesh&& other)                  = delete;
        Mesh& operator=(const Mesh& other)  = delete;
        Mesh& operator=(const Mesh&& other) = delete;

        virtual void Bind()   override;
        virtual void Unbind() override;
        virtual uint32_t GetVertexCount() override;
        virtual uint32_t GetIndexCount()  override;

        virtual const std::shared_ptr<Material>& GetMaterial() const;

    private:
        void createBuffers(const std::vector<Geometry::Vertex>& vertices, const std::vector<uint32_t>& indices);

        const uint32_t m_vertexCount;
        const uint32_t m_indicesCount;

        std::shared_ptr<Material> m_material = nullptr;

        Buffers::VertexArray                          m_vertexArray;
        std::shared_ptr<Buffers::VertexBuffer<float>> m_vertexBuffer = nullptr;
        std::unique_ptr<Buffers::IndexBuffer>         m_indexBuffer  = nullptr;
    };
}

#endif // ENGINE_RENDERER_RESOURCES_MESH_HPP_
