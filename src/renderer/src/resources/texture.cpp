#include "renderer/resources/texture.hpp"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Engine::Renderer::Resources
{
    Texture::~Texture()
    {
        glDeleteTextures(1, &m_info.Id);
    }

    void Texture::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_info.Id);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::unique_ptr<Texture> Texture::CreateFromFileUniquePtr(const std::filesystem::path& filePath,
                                                              Settings::ETextureFilteringMode firstFilter,
                                                              Settings::ETextureFilteringMode secondFilter,
                                                              bool generateMipmap, bool flip)
    {
        std::string name = filePath.string();

        GLuint textureID;
        int textureWidth;
        int textureHeight;
        int bitsPerPixel;
        glGenTextures(1, &textureID);

        stbi_set_flip_vertically_on_load(flip);
        unsigned char* dataBuffer = stbi_load(name.c_str(), &textureWidth, &textureHeight, &bitsPerPixel, 4);

        if (dataBuffer)
        {
            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataBuffer);

            if (generateMipmap)
                glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(firstFilter));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(secondFilter));

            stbi_image_free(dataBuffer);
            glBindTexture(GL_TEXTURE_2D, 0);

            TextureInfo info;
            info.Name = name;
            info.Id = textureID;
            info.Width = textureWidth;
            info.Height = textureHeight;
            info.Bpp = bitsPerPixel;
            info.FirstFilter = firstFilter;
            info.SecondFilter = secondFilter;
            info.GenerateMipmap = generateMipmap;

            Texture* texture = new Texture(info);
            return std::unique_ptr<Texture>(texture);
        }
        else
        {
            stbi_image_free(dataBuffer);
            glBindTexture(GL_TEXTURE_2D, 0);
            return nullptr;
        }
    }

    std::unique_ptr<Texture> Texture::CreateColorUniquePtr(const std::string& name, uint32_t data,
                                                           Settings::ETextureFilteringMode firstFilter,
                                                           Settings::ETextureFilteringMode secondFilter,
                                                           bool generateMipmap)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);

        if (generateMipmap)
            glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(firstFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(secondFilter));

        glBindTexture(GL_TEXTURE_2D, 0);

        TextureInfo info;
        info.Name = name;
        info.Id = textureID;
        info.Width = 1;
        info.Height = 1;
        info.Bpp = 32;
        info.FirstFilter = firstFilter;
        info.SecondFilter = secondFilter;
        info.GenerateMipmap = generateMipmap;

        Texture* texture = new Texture(info);
        return std::unique_ptr<Texture>(texture);
    }

    std::unique_ptr<Texture> Texture::CreateFromMemoryUniquePtr(const std::string& name, uint8_t* data,
                                                                uint32_t width, uint32_t height,
                                                                Settings::ETextureFilteringMode firstFilter,
                                                                Settings::ETextureFilteringMode secondFilter,
                                                                bool generateMipmap)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        if (generateMipmap)
            glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(firstFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(secondFilter));

        glBindTexture(GL_TEXTURE_2D, 0);

        TextureInfo info;
        info.Name = name;
        info.Id = textureID;
        info.Width = 1;
        info.Height = 1;
        info.Bpp = 32;
        info.FirstFilter = firstFilter;
        info.SecondFilter = secondFilter;
        info.GenerateMipmap = generateMipmap;

        Texture* texture = new Texture(info);
        return std::unique_ptr<Texture>(texture);
    }
}
