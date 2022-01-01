#include "VertexArray.hpp"

namespace sj
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &vao);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &vao);
    }

    void VertexArray::addBuffer(const VertexBuffer& vb, const VBLayout& layout)
    {
        bind();
        vb.bind();
        auto attributes = layout.getAttributes();
        unsigned int offset = 0;
        for (size_t i = 0; i < attributes.size(); ++i)
        {
            const auto& attribute = attributes[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.count, attribute.type, 
                attribute.normalized, layout.getStride(), reinterpret_cast<const void*>((const intptr_t)offset));
            offset += attribute.count * attribute.typeSize();
        }
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(vao);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }
}

