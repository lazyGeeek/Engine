#pragma once
#ifndef ENGINE_RENDERER_RESOURCES_TEXTURE_HPP_
#define ENGINE_RENDERER_RESOURCES_TEXTURE_HPP_

#include <memory>
#include <filesystem>
#include <string>

#include "renderer/settings/texture_filtering_mode.hpp"

namespace Engine::Renderer::Resources
{
    struct TextureInfo
    {
        std::string Name;
        uint32_t Id;
        uint32_t Width;
        uint32_t Height;
        uint32_t Bpp;
        Settings::ETextureFilteringMode FirstFilter;
        Settings::ETextureFilteringMode SecondFilter;
        bool GenerateMipmap;
    };

    class Texture
    {
    public:
        ~Texture();

        Texture(const Texture& other)             = delete;
        Texture(Texture&& other)                  = delete;
        Texture& operator=(const Texture& other)  = delete;
        Texture& operator=(const Texture&& other) = delete;

        void Bind(uint32_t slot = 0) const;
        void Unbind() const;

        static std::unique_ptr<Texture> CreateFromFileUniquePtr(const std::filesystem::path& filePath,
                                                                Settings::ETextureFilteringMode firstFilter,
                                                                Settings::ETextureFilteringMode secondFilter,
                                                                bool generateMipmap, bool flip);

        static std::unique_ptr<Texture> CreateColorUniquePtr(const std::string& name, uint32_t data,
                                                             Settings::ETextureFilteringMode firstFilter,
                                                             Settings::ETextureFilteringMode secondFilter,
                                                             bool generateMipmap);

        static std::unique_ptr<Texture> CreateFromMemoryUniquePtr(const std::string& name, uint8_t* data,
                                                                  uint32_t width, uint32_t height,
                                                                  Settings::ETextureFilteringMode firstFilter,
                                                                  Settings::ETextureFilteringMode secondFilter,
                                                                  bool generateMipmap);

    private:
        Texture(const TextureInfo& info) : m_info { info } { }

        TextureInfo m_info;
    };
}

#endif // ENGINE_RENDERER_RESOURCES_TEXTURE_HPP_
