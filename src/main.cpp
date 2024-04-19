#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "argh/argh.h"
#include "lib/engine/tests/Test.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "utils/String.h"
#include "utils/OpenGL.h"
#include "utils/FileReader.h"

#include "lib/draw/Shader.h"
#include "lib/draw/Renderer.h"
#include "lib/draw/Texture.h"

#include "lib/engine/tests/TestMenu.h"
#include "lib/engine/tests/TestClearColor.h"

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

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    argh::parser io(argv);
    if (io[{"gld", "gldebug"}])
    {
        GLCall(std::cout << "[DEBUG]: OpenGL Version -> " << glGetString(GL_VERSION) << std::endl);
    }

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init((char *)glGetString(330));

    test::Test *currentTest = nullptr;

    test::TestMenu *testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("Home"))
            {
                delete currentTest;
                currentTest = testMenu;
            }

            currentTest->OnImGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete currentTest;
    if (currentTest != testMenu)
        delete testMenu;

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
