#pragma once
#ifndef ENGINE_RENDERER_RESOURCES_MODEL_HPP_
#define ENGINE_RENDERER_RESOURCES_MODEL_HPP_

#include <filesystem>
#include <list>
#include <memory>
#include <string>

namespace Engine::Renderer::Resources
{
    class Mesh;

    class Model
    {
    public:
        ~Model();

        Model(const Model& other)             = delete;
        Model(Model&& other)                  = delete;
        Model& operator=(const Model& other)  = delete;
        Model& operator=(const Model&& other) = delete;

        const std::list<std::shared_ptr<Mesh>>& GetMeshes() const;

        void SetMeshes(const std::list<std::shared_ptr<Mesh>>& meshes);

        static std::unique_ptr<Model> CreatePtr();

    private:
        Model() = default;

        std::list<std::shared_ptr<Mesh>> m_meshes;
    };
}

#endif // ENGINE_RENDERER_RESOURCES_MODEL_HPP_
