/*
  Engine.cpp
  Created: April 19, 2024
*/

#include "Engine.h"

Engine::Engine(GLFWwindow *window)
    : m_Window(window), m_Renderer(), m_CurrentTest(nullptr)
{
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init((char *)glGetString(330));

    ImGuiIO &io = ImGui::GetIO();
    ImGuiStyle &style = ImGui::GetStyle();

    io.LogFilename = nullptr;
    io.IniFilename = nullptr;

    m_TestMenu = new test::TestMenu(m_CurrentTest);
    m_CurrentTest = new test::TestCamera();

    m_TestMenu->RegisterTest<test::TestClearColor>("Clear Color");
    m_TestMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
    m_TestMenu->RegisterTest<test::TestTexture3D>("Texture 3D");
    m_TestMenu->RegisterTest<test::TestCamera>("Camera");
}

Engine::~Engine()
{

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    delete m_CurrentTest;
    if (m_CurrentTest != m_TestMenu)
        delete m_TestMenu;
}

void Engine::Render()
{
    m_Renderer.Clear();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (m_CurrentTest && DEBUG)
    {
        m_CurrentTest->OnUpdate(0.0f);
        m_CurrentTest->OnRender();
        ImGui::Begin("Test");
        if (m_CurrentTest != m_TestMenu && ImGui::Button("Home"))
        {
            delete m_CurrentTest;
            m_CurrentTest = m_TestMenu;
        }

        m_CurrentTest->OnImGuiRender();

        // ImGui::Space();
        ImGui::End();

        if (DEBUG)
        {
            if (KEYS.active.find("T") != KEYS.active.end())
                ImGui::ShowDemoWindow();

            ImGui::Begin("Debug");

            RenderFPS();
            // ImGui::Text("Window Contains Mouse: " << MOUSE.hovering ? "True" : "False");
            ImGui::Text("Window Size: (%i, %i)", WINDOW.width, WINDOW.height);

            bool hovering = MOUSE.hovering;
            ImGui::Checkbox("Window Contains Mouse", &hovering);
            bool dragging = MOUSE.dragging;
            ImGui::Checkbox("Mouse Dragging", &dragging);
            ImGui::Text("Mouse Position (%.1f, %.1f)", MOUSE.position[0], MOUSE.position[1]);
            ImGui::Text("Drag Start (%.1f, %.1f)", MOUSE.dragStart[0], MOUSE.dragStart[1]);
            ImGui::Text("Drag Offset (%.1f, %.1f)", MOUSE.dragOffset[0], MOUSE.dragOffset[1]);
            ImGui::Text("Scroll (%.1f, %.1f)", MOUSE.scrollOffset[0], MOUSE.scrollOffset[1]);

            bool left = MOUSE.leftHeld;
            bool mid = MOUSE.midHeld;
            bool right = MOUSE.rightHeld;

            ImGui::Text("Mouse Buttons:");
            ImGui::SameLine();
            ImGui::Checkbox("##left", &left);
            ImGui::SameLine();
            ImGui::Checkbox("##mid", &mid);
            ImGui::SameLine();
            ImGui::Checkbox("##left", &right);

            ImGui::End();
        }
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}
