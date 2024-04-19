/*
  TestTexture2D.h
  Created: April 18, 2024
*/

#pragma once

#include "Test.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

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

  class TestTexture2D : public Test
  {
  public:
    TestTexture2D();
    ~TestTexture2D();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnImGuiRender() override;

  private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texture;

    glm::vec3 m_TranslationA, m_TranslationB;
    glm::mat4 m_ProjectionMatrix, m_ViewMatrix;
  };
}