#ifndef SJ_VERTEX_BUFFER
#define SJ_VERTEX_BUFFER
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace sj
{
    class VertexBuffer
    {
    public:
        VertexBuffer(const void* vb_data, size_t size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
    
    private:
        unsigned int g_buffer;
    };
}

#endif 