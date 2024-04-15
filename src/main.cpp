#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "utils/arg.h"
#include "utils/String.h"
#include "lib/FileReader.h"
#include "lib/Shader.h"

int main(int, char *argv[])
{
    if (!glfwInit())
        return -1;

    GLFWwindow *window;
    window = glfwCreateWindow(480, 480, "MGL", NULL, NULL);
    if (!window)
    {
        std::cout << "[GLFW ERROR]: Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "[GLEW ERROR]: Failed to initialize" << std::endl;
        return -1;
    }

    argh::parser io(argv);
    if (io[{"gld", "gldebug"}])
    {
        std::cout << "[DEBUG]: OpenGL Version -> " << glGetString(GL_VERSION) << std::endl;
    }

    float vertexes[] = {
        -0.5f, -0.5f, //
        0.5f, -0.5,   //
        0.5f, 0.5f,   //
        -0.5f, 0.5,   //

    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertexes, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    std::string rawShader = ReadFile("static/shader.glsl");
    ShaderProgramSource shaders = ParseShader(rawShader);

    // std::string vertexShader = ReadFile("static/shaders/vertex.glsl");
    // std::string fragmentShader = ReadFile("static/shaders/fragment.glsl");
    unsigned int shaderId = CreateShader(shaders.VertexSource, shaders.FragmentSource);
    glUseProgram(shaderId);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shaderId);
    glfwTerminate();
    return 0;
}
