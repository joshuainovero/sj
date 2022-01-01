#include "VertexBuffer.hpp"

namespace sj
{
    VertexBuffer::VertexBuffer(const void* vb_data, size_t size)
    {
        glGenBuffers(1, &g_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, g_buffer);
        glBufferData(GL_ARRAY_BUFFER, size, vb_data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &g_buffer);
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, g_buffer);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}