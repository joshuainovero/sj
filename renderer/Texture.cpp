#include "Texture.hpp"
#include <stb_image/stb_image.h>

namespace sj
{
    Texture::Texture(const std::string& path)
        : g_width(0), g_height(0), g_BPP(0)
    {
        stbi_set_flip_vertically_on_load(1);
        imageBuffer = stbi_load(path.c_str(), &g_width, &g_height, &g_BPP, 4);

        glGenTextures(1, &g_buffer);
        glBindTexture(GL_TEXTURE_2D, g_buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_width, g_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &g_buffer);
    }
    
    void Texture::bind(const unsigned int& slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, g_buffer);
    }

    void Texture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}