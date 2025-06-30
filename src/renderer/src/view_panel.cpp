#include "renderer/view_panel.hpp"
#include "renderer/resources/material.hpp"
#include "renderer/resources/model.hpp"
#include "renderer/resources/shader.hpp"
#include "renderer/resources/texture.hpp"
#include "renderer/resources/parsers/assimp_parser.hpp"

#include "ui/widgets/visuals/image.hpp"

#include "logs/logger.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine::Renderer
{
    ViewPanel::ViewPanel(const std::filesystem::path& projectPath) : UI::Panels::WindowPanel("View")
    {
        DisablePaddings(true);

        m_windowSettings.Scrollable = false;
        m_renderImage = CreateWidget<UI::Widgets::Visuals::Image>(m_fbo.GetRenderTextureId());

        Resources::ShaderInfo info;
        info.Name = "Base";
        info.Vertex = projectPath / "Shaders/vertex.glsl";
        info.Fragment = projectPath / "Shaders/fragment.glsl";

        m_shader = std::move(Resources::Shader::CreateUniquePtr(info));

        if (!m_shader)
            LOG_ERROR("Can't create base shader");

        Resources::Parsers::AssimpParser assimpParser;
        Resources::Parsers::EAssimpParserFlags parserFlags = Resources::Parsers::EAssimpParserFlags::CalcTangentSpace      |
                                                             Resources::Parsers::EAssimpParserFlags::JoinIdenticalVertices |
                                                             Resources::Parsers::EAssimpParserFlags::Triangulate           |
                                                             Resources::Parsers::EAssimpParserFlags::GenSmoothNormals      |
                                                             Resources::Parsers::EAssimpParserFlags::FlipUVs               |
                                                             Resources::Parsers::EAssimpParserFlags::ImproveCacheLocality  |
                                                             Resources::Parsers::EAssimpParserFlags::FindInvalidData       |
                                                             Resources::Parsers::EAssimpParserFlags::GenUVCoords           |
                                                             Resources::Parsers::EAssimpParserFlags::FindInstances         |
                                                             Resources::Parsers::EAssimpParserFlags::OptimizeMeshes        |
                                                             Resources::Parsers::EAssimpParserFlags::OptimizeGraph         |
                                                             Resources::Parsers::EAssimpParserFlags::Debone                |
                                                             Resources::Parsers::EAssimpParserFlags::GlobalScale;

        m_cube = assimpParser.LoadModel(projectPath / "Models/cube/cube.obj", parserFlags);

        if (!m_cube)
            LOG_INFO("Can't create test cube");
    }

    void ViewPanel::DrawImpl()
    {
        glm::vec2 size = GetContentSize();
        m_renderImage->Resize(size);
        m_fbo.Resize(static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y));

        m_fbo.Bind();

        m_openGL.SetClearColor(0.0f, 0.2f, 0.4f, 1.0f);
        m_openGL.Clear();

        m_openGL.SetViewPort(0, 0, size.x, size.y);

        for (const std::shared_ptr<Resources::Mesh>& mesh : m_cube->GetMeshes())
        {
            std::shared_ptr<Resources::Material> material = mesh->GetMaterial();

            (material->HasDepthTest() ? glEnable : glDisable)(static_cast<GLenum>(Settings::ERenderingCapability::DepthTest));

            material->Bind(m_shader);
            mesh->Bind();

            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
            projection = glm::perspective(glm::radians(45.0f), size.x / size.y, 0.1f, 100.0f);

            m_shader->SetUniformMat4("model", model);
            m_shader->SetUniformMat4("view", view);
            m_shader->SetUniformMat4("projection", projection);

            m_openGL.Draw(mesh);

            mesh->Unbind();
            material->Unbind(m_shader);
        }

        m_fbo.Unbind();

        UI::Panels::WindowPanel::DrawImpl();
    }
}
