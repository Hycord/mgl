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
    window = glfwCreateWindow(960, 540, "MGL", NULL, NULL);
    if (!window)
    {
        std::cout << "[GLFW ERROR]: Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glfwSwapInterval(1);

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
        -50.0f, -50.0f, 0.0f, 0.0f, // 0
        50.0f, -50.0f, 1.0f, 0.0f,  // 1
        50.0f, 50.0f, 1.0f, 1.0f,   // 2
        -50.0f, 50.0f, 0.0f, 1.0f,  // 3
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

    glm::mat4 projectionMatrix = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Shader shader("static/shader.glsl");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);

    Texture texture("static/textures/minecraft.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    vertexArray.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();
    shader.Unbind();

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init((char *)glGetString(330));

    // ImGuiIO &io = ImGui::GetIO();
    // (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    glm::vec3 translation(0, 0, 0);

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix; // must be in reverse order. matrix multiplication is _not_ commutitive

        shader.Bind();
        shader.SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvpMatrix);

        renderer.Draw(vertexArray, indexBuffer, shader);

        static float f = 0.0f;
        static int counter = 0;

        {
            ImGui::SliderFloat("X", &translation.x, 0.0f, 960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Y", &translation.y, 0.0f, 540.0f); // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Z", &translation.z, 0.0f, 1.0f);   // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::Text("%.3f ms (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ImGui::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();
    return 0;
}
