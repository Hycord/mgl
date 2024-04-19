/*
  TestClearColor.cpp
  Created: April 18, 2024
*/

#include "TestClearColor.h"
#include <GL/glew.h>
#include "../../../utils/OpenGL.h"

#include "../../../vendor/imgui/imgui.h"
#include "../../../vendor/imgui/imgui_impl_glfw.h"
#include "../../../vendor/imgui/imgui_impl_opengl3.h"

namespace test
{

  TestClearColor::TestClearColor()
      : m_ClearColor{0.32f, 0.78f, 0.7f, 1.0f} {};

  // TestClearColor::~TestClearColor(){};

  // void TestClearColor::OnUpdate(float deltaTime){};
  void TestClearColor::OnRender()
  {
    GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
  };
  void TestClearColor::OnImGuiRender()
  {
    ImGui::ColorEdit4("Clear Color", m_ClearColor);
  };
}