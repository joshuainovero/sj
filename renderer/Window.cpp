#include "Window.hpp"
#include <assert.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
namespace sj
{
    Window::Window(const char* title, uint32_t width, uint32_t height, bool contextState)
        : m_Width(width), m_Height(height)
    {
        glfwInit();
        window = glfwCreateWindow(m_Width, m_Height, title, nullptr, nullptr);

        if (contextState)
            glfwMakeContextCurrent(window);

        assert(glewInit() == GLEW_OK);

        view_ = glm::mat4(1.0f);
        proj_ = glm::ortho(-((width)/2.0f), width/2.0f, -((height)/2.0f), height/2.0f, -1.0f, 1.0f);

    }

    Window::~Window()
    {
        close();
    }

    void Window::draw(const VertexArray& va, const IndexBuffer& ib, const ShaderFile& shader)
    {
        va.bind();
        ib.bind();
        shader.bind();
        glDrawElements(GL_TRIANGLES, ib.count(), GL_UNSIGNED_INT, nullptr);
    }

    void Window::draw(const RenderObject<float>& object)
    {
        object.bind();
        glm::mat4 mvp = proj_ * view_ * (object.model());
        glUniformMatrix4fv(glGetUniformLocation(object.shaderID(), "u_MVP"), 1, GL_FALSE, &mvp[0][0]);
        glDrawElements(GL_TRIANGLES, object.ib_count(), GL_UNSIGNED_INT, nullptr);
    }

    void Window::useWindow()
    {
        glfwMakeContextCurrent(window);
    }

    void Window::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    void Window::close()
    {
        glfwTerminate();
    }

    bool Window::isOpen()
    {
        return !glfwWindowShouldClose(window);
    }

    [[nodiscard]] uint32_t Window::width()
    {
        return m_Width;
    }

    [[nodiscard]] uint32_t Window::height()
    {
        return m_Height;
    }

    [[nodiscard]] glm::mat4 Window::view()
    {
        return view_;
    }

    [[nodiscard]] glm::mat4 Window::projection()
    {
        return proj_;
    }
}