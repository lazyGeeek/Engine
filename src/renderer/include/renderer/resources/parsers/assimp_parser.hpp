#pragma once
#ifndef ENGINE_RENDERER_RESOURCES_PARSERS_ASSIMP_PARSER_HPP_
#define ENGINE_RENDERER_RESOURCES_PARSERS_ASSIMP_PARSER_HPP_

#include <filesystem>
#include <list>
#include <memory>
#include <optional>

#include "renderer/resources/mesh.hpp"

#include <assimp/matrix4x4.h>

#include "renderer/resources/parsers/assimp_parser_flags.hpp"
#include "renderer/geometry/vertex.hpp"

struct aiScene;
struct aiMesh;
struct aiNode;

namespace Engine::Renderer::Resources { class Material; class Model; }

namespace Engine::Renderer::Resources::Parsers
{
    class AssimpParser
    {
    public:
        std::shared_ptr<Renderer::Resources::Model> LoadModel(const std::filesystem::path& filePath, EAssimpParserFlags assimpFlags);

    private:
        std::shared_ptr<Renderer::Resources::Material> createMaterial(const struct aiScene* scene, int index);
        std::list<std::shared_ptr<Renderer::Resources::Mesh>> processNode(aiMatrix4x4& transform, struct aiNode* node, const struct aiScene* scene);
        void processMesh(const aiMatrix4x4& transform, struct aiMesh* mesh, const struct aiScene* scene, std::vector<Renderer::Geometry::Vertex>& outVertices, std::vector<uint32_t>& outIndices);

        std::filesystem::path m_filePath = "";
    };
}

#endif // ENGINE_RENDERER_RESOURCES_PARSERS_ASSIMP_PARSER_HPP_
