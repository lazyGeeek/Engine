#include "renderer/resources/parsers/assimp_parser.hpp"
#include "renderer/resources/material.hpp"
#include "renderer/resources/model.hpp"
#include "renderer/resources/texture.hpp"

#include "tools/utils/path_parser.hpp"

#include <assimp/Importer.hpp>
#include <assimp/matrix4x4.h>
#include <assimp/scene.h>

using MaterialPtr = std::shared_ptr<Engine::Renderer::Resources::Material>;
using ModelPtr = std::shared_ptr<Engine::Renderer::Resources::Model>;

namespace Engine::Renderer::Resources::Parsers
{
    ModelPtr AssimpParser::LoadModel(const std::filesystem::path& filePath, EAssimpParserFlags assimpFlags)
    {
        m_filePath = filePath;

        Assimp::Importer import;
        const aiScene * scene = import.ReadFile(filePath.string(), static_cast<unsigned int>(assimpFlags));

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            return nullptr;

        aiMatrix4x4 identity;
        ModelPtr model = std::move(Model::CreatePtr());

        model->SetMeshes(processNode(identity, scene->mRootNode, scene));

        return model;
    }

    MaterialPtr AssimpParser::createMaterial(const aiScene* scene, int index)
    {
        aiMaterial* material = scene->mMaterials[index];
        if (material)
        {
            aiString name;
            aiGetMaterialString(material, AI_MATKEY_NAME, &name);
            std::shared_ptr<Material> newMat = std::move(Material::CreatePtr());

            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                aiString diffuse;
                aiGetMaterialString(material, AI_MATKEY_TEXTURE_DIFFUSE(0), &diffuse);
                std::filesystem::path diffusePath = m_filePath.parent_path() / diffuse.C_Str();

                std::unique_ptr<Texture> newTexture = Texture::CreateFromFileUniquePtr(diffusePath,
                    Settings::ETextureFilteringMode::LinearMipmapLinear,
                    Settings::ETextureFilteringMode::Linear, true, false);
                newMat->SetDiffuse(std::move(newTexture));
            }

            return newMat;
        }

        return nullptr;
    }

    std::list<std::shared_ptr<Resources::Mesh>> AssimpParser::processNode(aiMatrix4x4& transform, aiNode* node, const aiScene* scene)
    {
        std::list<std::shared_ptr<Resources::Mesh>> meshes;
        aiMatrix4x4 nodeTransformation = transform * node->mTransformation;

        // Process all the node's meshes (if any)
        for (uint32_t i = 0; i < node->mNumMeshes; ++i)
        {
            std::vector<Geometry::Vertex> vertices;
            std::vector<uint32_t> indices;
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(nodeTransformation, mesh, scene, vertices, indices);
            MaterialPtr newMaterial = createMaterial(scene, mesh->mMaterialIndex);
            meshes.emplace_back(std::make_shared<Mesh>(vertices, indices, newMaterial));
        }

        // Then do the same for each of its children
        for (uint32_t i = 0; i < node->mNumChildren; ++i)
        {
            std::list<std::shared_ptr<Resources::Mesh>> newMeshes = processNode(nodeTransformation, node->mChildren[i], scene);
            meshes.insert(meshes.end(), newMeshes.begin(), newMeshes.end());
        }

        return meshes;
    }

    void AssimpParser::processMesh(const aiMatrix4x4& transform, aiMesh* mesh, const aiScene* scene, std::vector<Geometry::Vertex>& outVertices, std::vector<uint32_t>& outIndices)
    {
        for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
        {
            aiVector3D position = transform * mesh->mVertices[i];
            aiVector3D normal = transform * (mesh->mNormals ? mesh->mNormals[i] : aiVector3D(0.0f, 0.0f, 0.0f));
            aiVector3D texCoords = mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i] : aiVector3D(0.0f, 0.0f, 0.0f);
            aiVector3D tangent = mesh->mTangents ? transform * mesh->mTangents[i] : aiVector3D(0.0f, 0.0f, 0.0f);
            aiVector3D bitangent = mesh->mBitangents ? transform * mesh->mBitangents[i] : aiVector3D(0.0f, 0.0f, 0.0f);

            outVertices.push_back
            ({
                { position.x,  position.y,  position.z },
                { texCoords.x, texCoords.y },
                { normal.x,    normal.y,    normal.z },
                { tangent.x,   tangent.y,   tangent.z },
                { bitangent.x, bitangent.y, bitangent.z }
            });
        }

        for (uint32_t faceID = 0; faceID < mesh->mNumFaces; ++faceID)
        {
            aiFace face = mesh->mFaces[faceID];

            for (size_t indexID = 0; indexID < face.mNumIndices; ++indexID)
                outIndices.push_back(face.mIndices[indexID]);
        }
    }
}
