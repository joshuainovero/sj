#ifndef SJ_RENDER_OBJECT_H
#define SJ_RENDER_OBJECT_H
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <memory>

namespace sj
{

    template <typename T>
    class RenderObject
    {
    public:
        RenderObject(std::vector<T>&& vp_, std::vector<unsigned int>&& ip_)
        {
            va = std::make_unique<sj::VertexArray>();
            
            v_size = vp_.size();
            v_positions = new T[v_size];
            for (size_t i = 0; i < v_size; ++i)
            {
                v_positions[i] = vp_[i];
            }
            vb = std::make_unique<sj::VertexBuffer>(v_positions, sizeof(T) * v_size);
            
            indices_count = ip_.size();
            indices = new unsigned int[indices_count];
            for (size_t i = 0; i < indices_count; ++i)
            {
                indices[i] = ip_[i];
            }
            ib = std::make_unique<sj::IndexBuffer>(indices, indices_count);
            layout = std::make_unique<sj::VBLayout>();

            shader = std::make_unique<sj::ShaderFile>("shader/vert.shader", "shader/frag.shader");

            model_ = glm::mat4(1.0f);
            

        }
        ~RenderObject()
        {
        }
        inline void modifyModel(glm::mat4 mod_);

        inline void bind() const
        {
            va->bind();
            shader->bind();
            ib->bind();
        }

        inline void addAttribute(const int& count, const unsigned int& type)
        {
            layout->addAttribute(count, type);
            va->addBuffer(*vb, *layout);
        }

        inline unsigned int shaderID() const { return shader->shaderID(); }
        inline unsigned int ib_count() const { return indices_count; }
        inline glm::mat4 model() const  { return model_; }

    private:
        std::unique_ptr<sj::VertexArray> va;
        std::unique_ptr<sj::VertexBuffer> vb;
        std::unique_ptr<sj::IndexBuffer> ib;
        std::unique_ptr<sj::VBLayout> layout;
        glm::mat4 model_;
        std::unique_ptr<sj::ShaderFile> shader;
    
        T* v_positions;
        unsigned int* indices;
        size_t v_size;
        size_t indices_count;

    };  
}

#endif