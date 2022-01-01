
#ifndef SJ_WINDOW_H
#define SJ_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "IndexBuffer.hpp"
#include "RenderObject.hpp"

namespace sj
{
    class Window
    {
    public:
        Window(const char* title, uint32_t width, uint32_t height, bool contextState);
        ~Window();

        void draw(const VertexArray& va, const IndexBuffer& ib, const ShaderFile& shader);

        void draw(const RenderObject<float>& ro);

        void useWindow();
        
        void clear();
        
        void swapBuffers();

        void pollEvents();

        void close();

        bool isOpen();

        [[nodiscard]] uint32_t width();
        [[nodiscard]] uint32_t height();
        [[nodiscard]] glm::mat4 view();
        [[nodiscard]] glm::mat4 projection();

    private:
        GLFWwindow* window;

        uint32_t m_Height, m_Width;

        glm::mat4 view_;

        glm::mat4 proj_;

    };
}

#endif // SJ_WINDOW_H