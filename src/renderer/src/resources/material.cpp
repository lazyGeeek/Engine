#include "renderer/resources/material.hpp"
#include "renderer/resources/shader.hpp"
#include "renderer/resources/texture.hpp"

namespace Engine::Renderer::Resources
{
    std::unique_ptr<Material> Material::CreatePtr()
    {
        Material* material = new Material();
        return std::unique_ptr<Material>(material);
    }

    void Material::Bind(const std::shared_ptr<Shader> shader)
    {
        shader->Bind();

        int textureSlot = 0;

        if (m_diffuse && shader->GetUniformInfo("diffuse").has_value())
        {
            m_diffuse->Bind(textureSlot);
            shader->SetUniformInt("diffuse", textureSlot++);
        }
    }

    void Material::Unbind(const std::shared_ptr<Shader> shader)
    {
        shader->Unbind();
    }

    void Resources::Material::SetDepthTest(bool depthTest)
    {
        m_depthTest = depthTest;
    }

    void Material::SetDiffuse(const std::shared_ptr<Texture>& diffuse)
    {
        m_diffuse = diffuse;
    }

    bool Material::HasDepthTest() const
    {
        return m_depthTest;
    }

    const std::shared_ptr<Texture> Material::GetDiffuse() const
    {
        return m_diffuse;
    }
}
