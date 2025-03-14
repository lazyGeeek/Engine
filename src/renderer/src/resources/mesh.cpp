#include "renderer/resources/mesh.hpp"
#include "renderer/resources/material.hpp"
#include "renderer/buffers/index_buffer.hpp"
#include "renderer/buffers/vertex_buffer.hpp"
#include "renderer/geometry/vertex.hpp"

#include <algorithm>

namespace Engine::Renderer::Resources
{
    Mesh::Mesh(const std::vector<Geometry::Vertex>& vertices,
        const std::vector<uint32_t>& indices,
        const std::shared_ptr<Material>& material) :
        m_vertexCount(static_cast<uint32_t>(vertices.size())),
        m_indicesCount(static_cast<uint32_t>(indices.size())),
        m_material { material }
    {
        createBuffers(vertices, indices);
    }

    Mesh::~Mesh()
    {
        if (m_material)
            m_material = nullptr;

        if (m_vertexBuffer)
            m_vertexBuffer = nullptr;

        if (m_indexBuffer)
            m_indexBuffer = nullptr;
    }

    void Mesh::Bind()
    {
        m_vertexArray.Bind();
    }

    void Mesh::Unbind()
    {
        m_vertexArray.Unbind();
    }

    uint32_t Mesh::GetVertexCount()
    {
        return m_vertexCount;
    }

    uint32_t Mesh::GetIndexCount()
    {
        return m_indicesCount;
    }

    const std::shared_ptr<Material>& Mesh::GetMaterial() const
    {
        return m_material;
    }

    void Mesh::createBuffers(const std::vector<Geometry::Vertex>& vertices, const std::vector<uint32_t>& indices)
    {
        std::vector<float> vertexData;
        std::vector<unsigned int> rawIndices;

        for (const auto& vertex : vertices)
        {
            vertexData.push_back(vertex.Position[0]);
            vertexData.push_back(vertex.Position[1]);
            vertexData.push_back(vertex.Position[2]);

            vertexData.push_back(vertex.TexCoords[0]);
            vertexData.push_back(vertex.TexCoords[1]);

            vertexData.push_back(vertex.Normals[0]);
            vertexData.push_back(vertex.Normals[1]);
            vertexData.push_back(vertex.Normals[2]);

            vertexData.push_back(vertex.Tangent[0]);
            vertexData.push_back(vertex.Tangent[1]);
            vertexData.push_back(vertex.Tangent[2]);

            vertexData.push_back(vertex.Bitangent[0]);
            vertexData.push_back(vertex.Bitangent[1]);
            vertexData.push_back(vertex.Bitangent[2]);
        }

        m_vertexBuffer = std::make_shared<Buffers::VertexBuffer<float>>(vertexData);
        m_indexBuffer = std::make_unique<Buffers::IndexBuffer>(const_cast<uint32_t*>(indices.data()), indices.size());

        uint64_t vertexSize = sizeof(Geometry::Vertex);

        m_vertexArray.BindAttribute(0, *m_vertexBuffer, Buffers::EType::Float, 3, vertexSize, offsetof(Geometry::Vertex, Position));
        m_vertexArray.BindAttribute(1, *m_vertexBuffer, Buffers::EType::Float, 2, vertexSize, offsetof(Geometry::Vertex, TexCoords));
        m_vertexArray.BindAttribute(2, *m_vertexBuffer, Buffers::EType::Float, 3, vertexSize, offsetof(Geometry::Vertex, Normals));
        m_vertexArray.BindAttribute(3, *m_vertexBuffer, Buffers::EType::Float, 3, vertexSize, offsetof(Geometry::Vertex, Tangent));
        m_vertexArray.BindAttribute(4, *m_vertexBuffer, Buffers::EType::Float, 3, vertexSize, offsetof(Geometry::Vertex, Bitangent));
    }
}
