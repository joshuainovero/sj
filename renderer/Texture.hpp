#ifndef SJ_TEXTURE_H
#define SJ_TEXTURE_H
#include <GL/glew.h>
#include <string>

namespace sj
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();

        void bind(const unsigned int& slot) const;
        void unbind() const;

    private:
        unsigned int g_buffer;
        unsigned char* imageBuffer;
        int g_width, g_height, g_BPP;
    };
}

#endif