#include "renderer/resources/model.hpp"
#include "renderer/resources/mesh.hpp"

namespace Engine::Renderer::Resources
{
    Model::~Model()
    {
        for (std::shared_ptr<Mesh>& mesh : m_meshes)
            mesh = nullptr;
    }

    std::unique_ptr<Model> Model::CreatePtr()
    {
        Model* model = new Model();
        return std::unique_ptr<Model>(model);
    }

    const std::list<std::shared_ptr<Mesh>>& Model::GetMeshes() const
    {
        return m_meshes;
    }

    void Model::SetMeshes(const std::list<std::shared_ptr<Mesh>>& meshes)
    {
        m_meshes = meshes;
    }
}
