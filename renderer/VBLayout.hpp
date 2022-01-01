#ifndef SJ_VB_LAYOUT_H
#define SJ_VB_LAYOUT_H
#include <GL/glew.h>
#include <vector>

namespace sj
{
    struct LayoutElements
    {
        int count;
        unsigned int type;
        unsigned char normalized;

        unsigned int typeSize() const;

    };

    class VBLayout
    {
    public:
        VBLayout();
        ~VBLayout();

        void addAttribute(const int& count, const unsigned int& type);

        std::vector<LayoutElements> getAttributes() const;
        int getStride() const;

    private:
        std::vector<LayoutElements> attributes;

        int g_stride;
    };
}

#endif