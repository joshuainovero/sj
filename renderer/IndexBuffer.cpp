#include "IndexBuffer.hpp"

namespace sj
{
    IndexBuffer::IndexBuffer(const void* ib_data, size_t count)
        : g_count(count)
    {
        glGenBuffers(1, &g_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, ib_data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &g_buffer);
    }

    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_buffer);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    size_t IndexBuffer::count() const
    {
        return g_count;
    }

}