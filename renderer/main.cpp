#include "Window.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "RenderObject.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <cmath>
#include <utility>

int main()
{

    sj::Window window("Window", 840, 580, true);


    sj::RenderObject<float> Square(
        {
            -200.0f, -200.0f, 0.0f, 0.0f,
             200.0f, -200.0f, 1.0f, 0.0f,
             200.0f,  200.0f, 1.0f, 1.0f,
            -200.0f,  200.0f, 0.0f, 1.0f
        },
        { 0, 1, 2, 2, 3, 0}
    );
    Square.addAttribute(2, GL_FLOAT);
    Square.addAttribute(2, GL_FLOAT);


    const float i_vertex_positions[] = {
        -200.0f, -200.0f, 0.01f, 0.182f,
        -100.0f, -200.0f + (200.0f * (std::sqrt(3.0f)/2.0f)), 0.5f, 0.97f,
         0.0f,   -200.0f, 0.95f, 0.182f
    };

    const float g_vertex_positions[] = {
        -200.0f, -200.0f,
        -100.0f, -200.0f + (200.0f * (std::sqrt(3.0f)/2.0f)),
         0.0f,   -200.0f,
         100.0f, -200.0f + (200.0f * (std::sqrt(3.0f)/2.0f)),
         200.0f, -200.0f,
         0.0f,  (-200.0f + (200.0f * (std::sqrt(3.0f)/2.0f)) * 2)
    };

    constexpr unsigned int i_indices[] = {
        0, 1, 2
    };

    constexpr unsigned int g_indices[] = {
        0, 1, 2,
        2, 3, 4,
        1, 3, 5
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Object 1
    sj::VertexArray i_va;
    sj::VertexBuffer i_vb(i_vertex_positions, sizeof(i_vertex_positions));
    sj::VBLayout i_layout;
    i_layout.addAttribute(2, GL_FLOAT);
    i_layout.addAttribute(2, GL_FLOAT);
    i_va.addBuffer(i_vb, i_layout);
    sj::IndexBuffer i_ib(i_indices, sizeof(i_indices)/sizeof(unsigned int));

    // Object 2
    sj::VertexArray g_va;
    sj::VertexBuffer g_vb(g_vertex_positions, sizeof(g_vertex_positions));
    sj::VBLayout g_layout;
    g_layout.addAttribute(2, GL_FLOAT);
    g_va.addBuffer(g_vb, g_layout);
    sj::IndexBuffer g_ib(g_indices, sizeof(g_indices)/sizeof(unsigned int));


    sj::ShaderFile shader("shader/vert.shader", "shader/frag.shader");
    shader.bind();


    glUniform4f(glGetUniformLocation(shader.shaderID(), "u_Color"), 1.0f, 0.65f, 0.0f, 1.0f);

    sj::Texture texture("resource/Illuminati-Logo.png");
    texture.bind(2);
    glUniform1i(glGetUniformLocation(shader.shaderID(), "u_Texture"), 2);

    glm::mat4 projection = glm::ortho(-420.0f, 420.0f, -290.0f, 290.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 mvp = projection * view * model;
    
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderID(), "u_MVP"), 1, GL_FALSE, &mvp[0][0]);

    std::vector<glm::mat4> models;
    models.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    models.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 0.0f, 0.0f)));
    models.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, (200.0f * (std::sqrt(3.0f)/2.0f)), 0.0f)));
    models.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, -225.5f, 0.0f)));
    models[models.size() - 1] = glm::rotate(models[models.size() - 1], glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));


    while (window.isOpen())
    {
        window.clear();
        shader.bind();

        for (const auto& model : models)
        {
            glm::mat4 mvp = window.projection() * window.view() * model;
            glUniformMatrix4fv(glGetUniformLocation(shader.shaderID(), "u_MVP"), 1, GL_FALSE, &mvp[0][0]);
            window.draw(i_va, i_ib, shader);
        }

        window.swapBuffers();

        window.pollEvents();
    }

    window.close();
    return 0;

}