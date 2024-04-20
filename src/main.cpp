#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "argh/argh.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "utils/String.h"
#include "utils/OpenGL.h"
#include "utils/FileReader.h"
#include "utils/Map.h"

#include "lib/draw/Shader.h"
#include "lib/draw/Renderer.h"
#include "lib/draw/Texture.h"

#include "lib/engine/Engine.h"

#include "lib/engine/tests/Test.h"
#include "lib/engine/tests/TestMenu.h"
#include "lib/engine/tests/TestClearColor.h"
#include "lib/engine/tests/TestTexture2D.h"

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
    window = glfwCreateWindow(960, 540, "MGL", NULL, NULL);
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

    Engine engine(window);

    glfwSetCursorPosCallback(window, OnCursorPosition);
    glfwSetCursorEnterCallback(window, OnCursorFocusChange);
    glfwSetMouseButtonCallback(window, OnMouseButtonStatusChange);
    glfwSetScrollCallback(window, OnMouseScroll);
    glfwSetKeyCallback(window, OnKeyboardStatusChange);

    argh::parser io(argv);
    if (io[{"d", "debug"}])
    {
        DEBUG = true;
    }

    if (DEBUG)
    {
        GLCall(std::cout << "[DEBUG]: OpenGL Version -> " << glGetString(GL_VERSION) << std::endl);
    }
    while (!glfwWindowShouldClose(window))
    {
        engine.Render();
    }

    return 0;
}
