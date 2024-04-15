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


    unsigned int buffer;
    glGenBuffers(1, &buffer);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    float pos[6] = {
        -0.5f, -0.5f, //
        0.0f, 0.05,   //
        0.5f, -0.5f,  //
    };
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

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

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, &buffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shaderId);
    glfwTerminate();
    return 0;
}
