#ifndef SJ_VERTEX_ARRAY_H
#define SJ_VERTEX_ARRAY_H
#include <GL/glew.h>
#include "VertexBuffer.hpp"
#include "VBLayout.hpp"

namespace sj
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(const VertexBuffer& vb, const VBLayout& layout);

        void bind() const;
        void unbind() const;
        
    private:
        unsigned int vao;
    };
}

#endif