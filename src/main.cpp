#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <string>

#include "vendor/argh.h"

#include "utils/String.h"
#include "utils/OpenGL.h"
#include "utils/FileReader.h"

#include "lib/draw/Shader.h"
#include "lib/draw/Renderer.h"
#include "lib/draw/Texture.h"

#include "lib/data/Buffer/IndexBuffer.h"
#include "lib/data/Buffer/VertexBuffer.h"
#include "lib/data/Array/VertexArray.h"

int main(int, char *argv[])
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(630, 480, "MGL", NULL, NULL);
    if (!window)
    {
        std::cout << "[GLFW ERROR]: Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "[GLEW ERROR]: Failed to initialize" << std::endl;
        return -1;
    }

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    argh::parser io(argv);
    if (io[{"gld", "gldebug"}])
    {
        GLCall(std::cout << "[DEBUG]: OpenGL Version -> " << glGetString(GL_VERSION) << std::endl);
    }

    float vertexes[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, //
        0.5f, -0.5, 1.0f, 0.0f,   //
        0.5f, 0.5f, 1.0f, 1.0f,   //
        -0.5f, 0.5f, 0.0f, 1.0f,  //
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(vertexes, 4 * 4 * sizeof(float));

    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(2);
    vbLayout.Push<float>(2);

    vertexArray.AddBuffer(vertexBuffer, vbLayout);

    IndexBuffer indexBuffer(indices, 6);

    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    Shader shader("static/shader.glsl");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);
    shader.SetUniformMat4f("u_MVP", proj);

    Texture texture("static/textures/minecraft.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    vertexArray.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();
    shader.Unbind();

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);

        renderer.Draw(vertexArray, indexBuffer, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
