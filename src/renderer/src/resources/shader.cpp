#include "renderer/resources/shader.hpp"
#include "logs/logger.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include <fstream>
#include <sstream>

namespace Engine::Renderer::Resources
{
    Shader::Shader(uint32_t id) :
        m_id { id }
    {
        queryUniforms();
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_id);
    }

    std::shared_ptr<Resources::Shader> Resources::Shader::CreateSharedPtr(const ShaderInfo& info)
    {
        uint32_t id = createProgram(info);
        if (!id) return nullptr;

        Resources::Shader* shader = new Resources::Shader(id);
        return std::shared_ptr<Resources::Shader>(shader);
    }

    std::unique_ptr<Resources::Shader> Resources::Shader::CreateUniquePtr(const ShaderInfo& info)
    {
        uint32_t id = createProgram(info);
        if (!id) return nullptr;

        Resources::Shader* shader = new Resources::Shader(id);
        return std::unique_ptr<Resources::Shader>(shader);
    }

    void Resources::Shader::Bind() const
    {
        glUseProgram(m_id);
    }

    void Resources::Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Resources::Shader::SetUniformInt(const std::string& name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Resources::Shader::SetUniformFloat(const std::string& name, float value)
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Resources::Shader::SetUniformVec2(const std::string& name, const glm::vec2& value)
    {
        glUniform2f(getUniformLocation(name), value.x, value.y);
    }

    void Resources::Shader::SetUniformVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Resources::Shader::SetUniformVec4(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Resources::Shader::SetUniformMat4(const std::string& name, const glm::mat4& value)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
    }

    int Resources::Shader::GetUniformInt(const std::string& name)
    {
        int value;
        glGetUniformiv(m_id, getUniformLocation(name), &value);
        return value;
    }

    float Resources::Shader::GetUniformFloat(const std::string& name)
    {
        float value;
        glGetUniformfv(m_id, getUniformLocation(name), &value);
        return value;
    }

    glm::vec2 Resources::Shader::GetUniformVec2(const std::string& name)
    {
        GLfloat values[2];
        glGetUniformfv(m_id, getUniformLocation(name), values);
        return glm::make_vec2(values);
    }

    glm::vec3 Resources::Shader::GetUniformVec3(const std::string& name)
    {
        GLfloat values[3];
        glGetUniformfv(m_id, getUniformLocation(name), values);
        return glm::make_vec3(values);
    }

    glm::vec4 Resources::Shader::GetUniformVec4(const std::string& name)
    {
        GLfloat values[4];
        glGetUniformfv(m_id, getUniformLocation(name), values);
        return glm::make_vec4(values);
    }

    glm::mat4 Resources::Shader::GetUniformMat4(const std::string& name)
    {
        GLfloat values[16];
        glGetUniformfv(m_id, getUniformLocation(name), values);
        return glm::make_mat4(values);
    }

    uint32_t Resources::Shader::getUniformLocation(const std::string& name)
    {
        if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
            return m_uniformLocationCache.at(name);

        const int location = glGetUniformLocation(m_id, name.c_str());

        m_uniformLocationCache[name] = location;

        return location;
    }

    void Resources::Shader::queryUniforms()
    {
        GLint numActiveUniforms = 0;
        m_uniforms.clear();
        glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
        std::vector<GLchar> nameData(256);
        for (int unif = 0; unif < numActiveUniforms; ++unif)
        {
            GLint arraySize = 0;
            GLenum type = 0;
            GLsizei actualLength = 0;
            glGetActiveUniform(m_id, unif, static_cast<GLsizei>(nameData.size()), &actualLength, &arraySize, &type, &nameData[0]);
            std::string name(static_cast<char*>(nameData.data()), actualLength);

            std::any defaultValue;
            switch (static_cast<UniformType>(type))
            {
                case UniformType::UniformBool:      defaultValue = std::make_any<bool>(GetUniformInt(name));       break;
                case UniformType::UniformInt:       defaultValue = std::make_any<int>(GetUniformInt(name));        break;
                case UniformType::UniformFloat:     defaultValue = std::make_any<float>(GetUniformFloat(name));    break;
                case UniformType::UniformFloatVec2: defaultValue = std::make_any<glm::vec2>(GetUniformVec2(name)); break;
                case UniformType::UniformFloatVec3: defaultValue = std::make_any<glm::vec3>(GetUniformVec3(name)); break;
                case UniformType::UniformFloatVec4: defaultValue = std::make_any<glm::vec4>(GetUniformVec4(name)); break;
                case UniformType::UniformFloatMat4: defaultValue = std::make_any<glm::mat4>(GetUniformMat4(name)); break;
                case UniformType::UniformSampler2D: defaultValue = std::make_any<int>(GetUniformInt(name));        break;
            }

            if (defaultValue.has_value())
            {
                m_uniforms.push_back
                ({
                    static_cast<UniformType>(type),
                    name,
                    getUniformLocation(nameData.data()),
                    defaultValue
                });
            }
        }
    }

    std::optional<std::reference_wrapper<const Resources::UniformInfo>> Resources::Shader::GetUniformInfo(const std::string& name) const
    {
        auto found = std::find_if(m_uniforms.begin(), m_uniforms.end(), [&name](const UniformInfo& element)
            {
                return name == element.Name;
            });

        if (found != m_uniforms.end())
            return std::make_optional(*found);
        else
            return std::nullopt;
    }

    uint32_t Shader::createProgram(const ShaderInfo& info)
    {
        const uint32_t program = glCreateProgram();

        const uint32_t vs = compileShader(GL_VERTEX_SHADER, info.Vertex);
        const uint32_t fs = compileShader(GL_FRAGMENT_SHADER, info.Fragment);

        uint32_t gs = 0;
        if (info.Geometry.has_value())
            gs = compileShader(GL_GEOMETRY_SHADER, info.Geometry.value());

        if (vs == 0 || fs == 0)
            return 0;

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        if (info.Geometry.has_value())
            glAttachShader(program, gs);

        glLinkProgram(program);

        GLint linkStatus;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        if (linkStatus == GL_FALSE)
        {
            GLint maxLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::string errorLog(maxLength, ' ');
            glGetProgramInfoLog(program, maxLength, &maxLength, errorLog.data());

            glDeleteProgram(program);

            LOG_ERROR(errorLog.c_str());

            return 0;
        }

        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);

        if (info.Geometry.has_value())
            glDeleteShader(gs);

        return program;
    }

    uint32_t Shader::compileShader(uint32_t type, const std::filesystem::path& path)
    {
        const uint32_t id = glCreateShader(type);

        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        file.open(path.string());

        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        std::string code = stream.str();
        const char* tmp = code.c_str();
        glShaderSource(id, 1, &tmp, nullptr);
        glCompileShader(id);

        GLint compileStatus;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

        if (compileStatus == GL_FALSE)
        {
            GLint maxLength;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            std::string errorLog(maxLength, ' ');
            glGetShaderInfoLog(id, maxLength, &maxLength, errorLog.data());

            std::string shaderTypeString = "VERTEX SHADER";

            if (type == GL_FRAGMENT_SHADER)
                shaderTypeString = "FRAGMENT SHADER";
            else if (type == GL_GEOMETRY_SHADER)
                shaderTypeString = "GEOMETRY SHADER";

            std::string errorHeader = "[" + shaderTypeString + "] \"";

            LOG_ERROR("[%s] %s", errorHeader.c_str(), errorLog.c_str());

            glDeleteShader(id);

            return 0;
        }

        return id;
    }
}
