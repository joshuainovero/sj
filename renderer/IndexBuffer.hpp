#ifndef SJ_INDEX_BUFFER_H
#define SJ_INDEX_BUFFER_H
#include <GL/glew.h>

namespace sj
{
    class IndexBuffer
    {
    public:
        IndexBuffer(const void* ib_data, size_t count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        size_t count() const;

    private:
        unsigned int g_buffer;

        size_t g_count;
    };
}


#endif