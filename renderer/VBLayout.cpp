#include "VBLayout.hpp"

namespace sj
{
    unsigned int LayoutElements::typeSize() const
    {
        switch(type)
        {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int); 
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char); 
            default: return 0; 
        }
    }

    VBLayout::VBLayout() : g_stride(0) {}
    VBLayout::~VBLayout() {}

    void VBLayout::addAttribute(const int& count, const unsigned int& type)
    {
        if (type == GL_FLOAT)
        {
            g_stride += sizeof(float) * count;
            attributes.push_back({count, type, GL_FALSE});
        }
        else if (type == GL_UNSIGNED_INT)
        {
            g_stride += sizeof(unsigned int) * count;
            attributes.push_back({count, type, GL_FALSE});
        }
        else if (type == GL_UNSIGNED_BYTE)
        {
            g_stride += sizeof(unsigned char) * count;
            attributes.push_back({count, type, GL_TRUE});
        }
    }

    std::vector<LayoutElements> VBLayout::getAttributes() const
    {
        return attributes;
    }

    int VBLayout::getStride() const
    {
        return g_stride;
    }
}