#include "ui/widgets/visuals/image.hpp"
#include "ui/internal/converter.hpp"

#include <imgui/imgui.h>

namespace Engine::UI::Widgets::Visuals
{
    Image::Image(uint32_t textureId) :
        BaseWidget("Image"), m_textureId { textureId } { }

    void Image::DrawImpl()
    {
        ImGui::Image(m_textureId.raw, Internal::Converter::ToImVec2(m_size), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
    }
}
