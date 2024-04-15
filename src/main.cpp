#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "lib/FileReader.h"
#include "lib/argh.h"

std::string repeat(const std::string &input, unsigned num)
{
    std::string ret;
    ret.reserve(input.size() * num);
    while (num--)
        ret += input;
    return ret;
}

static unsigned int CompileShader(unsigned int type, const std::string &source)
{

    unsigned int id = glCreateShader(type);

    const char *src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char *message = (char *)alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);

        std::string typeName = type == GL_VERTEX_SHADER ? "vertex" : "fragment";

        std::cout << "[SHADER ERROR]: Failed to compile " << typeName << " shader \n[" << typeName << " " << repeat("-", 10 - typeName.length()) << ">]: ";
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int programId = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programId, vs);
    glAttachShader(programId, fs);

    glLinkProgram(programId);
    glValidateProgram(programId);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return programId;
}


int main(int, char *argv[])
{
    argh::parser io(argv);

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "MSkia", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "[GLEW ERROR]: Failed to initialize" << std::endl;
        return -1;
    }

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

    std::string vertexShader = ReadFile("static/shaders/vertex.glsl");
    std::string fragmentShader = ReadFile("static/shaders/fragment.glsl");
    unsigned int shaderId = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shaderId);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
