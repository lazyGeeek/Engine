#pragma once
#ifndef ENGINE_UI_WIDGETS_VISUALS_IMAGE_HPP_
#define ENGINE_UI_WIDGETS_VISUALS_IMAGE_HPP_

#include "ui/widgets/base_widget.hpp"
#include "ui/widgets/interfaces/resizable.hpp"

#include <glm/glm.hpp>

namespace Engine::UI::Widgets::Visuals
{
    class Image : public BaseWidget, public Interfaces::Resizable
    {
    public:
        Image(uint32_t textureId);
        virtual ~Image() override = default;

        Image(const Image& other)             = delete;
        Image(Image&& other)                  = delete;
        Image& operator=(const Image& other)  = delete;
        Image& operator=(const Image&& other) = delete;

    protected:
        virtual void DrawImpl() override;

    private:
        union TextureId
        {
            uint32_t Id;
            void* raw;
        };

        TextureId m_textureId;
    };
}

#endif // ENGINE_UI_WIDGETS_VISUALS_IMAGE_HPP_
