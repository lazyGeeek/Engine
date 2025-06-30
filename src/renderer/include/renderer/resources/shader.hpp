#pragma once
#ifndef ENGINE_RENDERER_RESOURCES_SHADER_HPP_
#define ENGINE_RENDERER_RESOURCES_SHADER_HPP_

#include <filesystem>
#include <list>
#include <optional>
#include <unordered_map>

#include <glm/glm.hpp>

#include "renderer/resources/uniform_info.hpp"

namespace Engine::Renderer::Resources
{
    struct ShaderInfo
    {
        std::string Name;
        std::filesystem::path Vertex;
        std::filesystem::path Fragment;
        std::optional<std::filesystem::path> Geometry;
    };

    class Shader
    {
    public:
        ~Shader();

        Shader(const Shader& other)             = delete;
        Shader(Shader&& other)                  = delete;
        Shader& operator=(const Shader& other)  = delete;
        Shader& operator=(const Shader&& other) = delete;

        void Bind() const;
        void Unbind() const;
        void SetUniformInt(const std::string& name, int value);
        void SetUniformFloat(const std::string& name, float value);
        void SetUniformVec2(const std::string& name, const glm::vec2& value);
        void SetUniformVec3(const std::string& name, const glm::vec3& value);
        void SetUniformVec4(const std::string& name, const glm::vec4& value);
        void SetUniformMat4(const std::string& name, const glm::mat4& value);
        int GetUniformInt(const std::string& name);
        float GetUniformFloat(const std::string& name);
        glm::vec2 GetUniformVec2(const std::string& name);
        glm::vec3 GetUniformVec3(const std::string& name);
        glm::vec4 GetUniformVec4(const std::string& name);
        glm::mat4 GetUniformMat4(const std::string& name);

        std::optional<std::reference_wrapper<const UniformInfo>> GetUniformInfo(const std::string& name) const;

        static std::shared_ptr<Shader> CreateSharedPtr(const ShaderInfo& info);
        static std::unique_ptr<Shader> CreateUniquePtr(const ShaderInfo& info);

    private:
        Shader(uint32_t id);

        static uint32_t createProgram(const ShaderInfo& info);
        static uint32_t Shader::compileShader(uint32_t type, const std::filesystem::path& path);

        void queryUniforms();
        uint32_t getUniformLocation(const std::string& name);

        uint32_t m_id = 0;

        std::list<UniformInfo> m_uniforms;

        std::unordered_map<std::string, int> m_uniformLocationCache;
    };
}

#endif // ENGINE_RENDERER_RESOURCES_SHADER_HPP_
