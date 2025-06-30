#pragma once
#ifndef ENGINE_RENDERER_RESOURCES_MATERIAL_HPP_
#define ENGINE_RENDERER_RESOURCES_MATERIAL_HPP_

#include <any>
#include <filesystem>
#include <map>
#include <memory>

namespace Engine::Renderer::Resources
{
    class Shader;
    class Texture;

    class Material
    {
    public:
        void Bind(const std::shared_ptr<Shader> shader);
        void Unbind(const std::shared_ptr<Shader> shader);

        void SetDepthTest(bool depthTest);
        bool HasDepthTest() const;

        void SetDiffuse(const std::shared_ptr<Texture>& diffuse);
        const std::shared_ptr<Texture> GetDiffuse() const;

        static std::unique_ptr<Material> CreatePtr();

    private:
        Material() = default;

        bool m_depthTest = true;

        std::shared_ptr<Texture> m_diffuse = nullptr;
    };
}

#endif // ENGINE_RENDERER_RESOURCES_MATERIAL_HPP_
