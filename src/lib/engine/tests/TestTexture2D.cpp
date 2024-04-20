/*
  TestTexture2D.cpp
  Created: April 18, 2024
*/

#include "TestTexture2D.h"

namespace test
{

  TestTexture2D::TestTexture2D()
      : m_TranslationA(100, 200, 0),
        m_TranslationB(200, 400, 0),
        m_ProjectionMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_ViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))

  {
    float vertexes[] = {
        -50.0f, -50.0f, 0.0f, 0.0f, // 0
        50.0f, -50.0f, 1.0f, 0.0f,  // 1
        50.0f, 50.0f, 1.0f, 1.0f,   // 2
        -50.0f, 50.0f, 0.0f, 1.0f,  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    m_VertexArray = std::make_unique<VertexArray>();

    m_VertexBuffer = std::make_unique<VertexBuffer>(vertexes, 4 * 4 * sizeof(float));

    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(2);
    vbLayout.Push<float>(2);

    m_VertexArray->AddBuffer(*m_VertexBuffer, vbLayout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    m_Shader = std::make_unique<Shader>("defailt", "static/shaders/default.vs", "static/shaders/default.fs");
    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);

    m_Texture = std::make_unique<Texture>("static/textures/minecraft.png");
    m_Shader->SetUniform1i("u_Texture", 0);
  };
  TestTexture2D::~TestTexture2D(){};

  void TestTexture2D::OnUpdate(float deltaTime){};

  void TestTexture2D::OnRender()
  {
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    Renderer renderer;
    m_Texture->Bind();

    {
      glm::mat4 modelMatrixA = glm::translate(glm::mat4(1.0f), m_TranslationA);
      glm::mat4 mvpMatrix = m_ProjectionMatrix * m_ViewMatrix * modelMatrixA; // must be in reverse order. matrix multiplication is _not_ commutitive

      m_Shader->Bind();
      m_Shader->SetUniformMat4f("u_MVP", mvpMatrix);
      m_Shader->SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);

      renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

      glm::mat4 modelMatrixB = glm::translate(glm::mat4(1.0f), m_TranslationB);
      mvpMatrix = m_ProjectionMatrix * m_ViewMatrix * modelMatrixB; // must be in reverse order. matrix multiplication is _not_ commutitive
      m_Shader->SetUniformMat4f("u_MVP", mvpMatrix);
      renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
  };

  void TestTexture2D::OnImGuiRender()
  {
    ImGui::Text("A:");
    ImGui::SliderFloat("X##a", &m_TranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat("Y##a", &m_TranslationA.y, 0.0f, 540.0f);
    ImGui::SliderFloat("Z##a", &m_TranslationA.z, 0.0f, 1.0f);

    ImGui::Spacing();
    ImGui::Text("B:");
    ImGui::SliderFloat("X##b", &m_TranslationB.x, 0.0f, 960.0f);
    ImGui::SliderFloat("Y##b", &m_TranslationB.y, 0.0f, 540.0f);
    ImGui::SliderFloat("Z##b", &m_TranslationB.z, 0.0f, 1.0f);
  };
}