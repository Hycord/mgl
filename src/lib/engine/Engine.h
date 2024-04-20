/*
  Engine.h
  Created: April 19, 2024
*/

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

// #include "../../vendor/imgui/imgui.h"
// #include "../../vendor/imgui/imgui_impl_glfw.h"
// #include "../../vendor/imgui/imgui_impl_opengl3.h"

#include "../../utils/globals.h"
#include "../../utils/OpenGL.h"
#include "../../utils/ImGUI.h"

#include "../draw/Renderer.h"

#include "./tests/Test.h"
#include "./tests/TestMenu.h"
#include "./tests/TestClearColor.h"
#include "./tests/TestTexture2D.h"
#include "./tests/TestTexture3D.h"

class Engine
{
private:
    test::Test *m_CurrentTest;
    test::TestMenu *m_TestMenu;

    GLFWwindow *m_Window;
    Renderer m_Renderer;


public:
    Engine(GLFWwindow *window);
    ~Engine();

    void Render();
};