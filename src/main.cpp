#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "utils/arg.h"
#include "utils/String.h"
#include "utils/OpenGL.h"
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
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertexes, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    std::string rawShader = ReadFile("static/shader.glsl");
    ShaderProgramSource shaders = ParseShader(rawShader);

    // std::string vertexShader = ReadFile("static/shaders/vertex.glsl");
    // std::string fragmentShader = ReadFile("static/shaders/fragment.glsl");
    unsigned int shaderId = CreateShader(shaders.VertexSource, shaders.FragmentSource);
    GLCall(glUseProgram(shaderId));

    GLCall(int location = glGetUniformLocation(shaderId, "u_Color"));
    ASSERT((location != -1) == 1);
    GLCall(glUniform4f(location, 0.0f, 0.0f, 0.0f, 1.0f));

    float r = 0.32f;
    float increment = 0.01f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUniform4f(location, r, r, r, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f)
        {
            increment = -increment;
        }
        else if (r < 0.0f)
        {
            increment = -increment;
        }
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    GLCall(glDeleteProgram(shaderId));
    glfwTerminate();
    return 0;
}
