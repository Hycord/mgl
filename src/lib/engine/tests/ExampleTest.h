/*
  ExampleTest.h
  Created: April 18, 2024
*/

#pragma once

#include "Test.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../../../utils/OpenGL.h"

#include "../../data/Array/VertexArray.h"
#include "../../data/Buffer/IndexBuffer.h"
#include "../../data/Buffer/VertexBuffer.h"
#include "../../data/Buffer/VertexBufferLayout.h"

#include "../../draw/Shader.h"
#include "../../draw/Texture.h"
#include "../../draw/Renderer.h"

#include "../../../vendor/imgui/imgui.h"
#include "../../../vendor/imgui/imgui_impl_glfw.h"
#include "../../../vendor/imgui/imgui_impl_opengl3.h"

namespace test
{

  class ExampleTest : public Test
  {
  public:
    ExampleTest();
    ~ExampleTest();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;

  private:
  };
}