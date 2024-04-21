/*
  TestCamera.cpp
  Created: April 21, 2024
*/

#include "TestCamera.h"
#include "glm/gtc/type_ptr.hpp"

namespace test
{

  TestCamera::TestCamera()
      : m_Time(0),
        m_Rotation(0.0f),
        m_ProjectionMatrix(1.0f /* glm::ortho(0.0f, (float)WINDOW.width, 0.0f, (float)WINDOW.height, -1.0f, 1.0f) */),
        m_ViewMatrix(1.0f /* glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)) */),
        m_Camera(WINDOW.width, WINDOW.height, glm::vec3(0.0f, 0.0f, 1.0f))

  {
    float vertexes[] = {

        -0.5f, 0.0f, -0.5f,
        0.0f, 0.0f,
        //
        -0.5f, 0.0f, 0.5f,
        1.0f, 0.0f,
        //
        0.5f, 0.0f, 0.5f,
        0.0f, 0.0f,
        //
        0.5f, 0.0f, -0.5f,
        1.0f, 0.0f,
        //
        0.0f, 0.8f, 0.0f,
        0.5f, 1.0f

    };

    unsigned int indices[] = {
        0, 1, 4, // Base triangle 1
        4, 1, 2, // Base triangle 2
        2, 3, 4, // Base triangle 4
        4, 3, 0, // Base triangle 3
        0, 1, 2, // Side triangle 1
        2, 3, 0  // Side triangle 2
    };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    GLCall(glEnable(GL_DEPTH_TEST));

    m_VertexArray = std::make_unique<VertexArray>();

    m_VertexBuffer = std::make_unique<VertexBuffer>(vertexes, 5 * 5 * sizeof(float));

    VertexBufferLayout vbLayout;
    vbLayout.Push<float>(3);
    vbLayout.Push<float>(2);

    m_VertexArray->AddBuffer(*m_VertexBuffer, vbLayout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));

    m_Shader = std::make_unique<Shader>("defailt", "static/shaders/default.vs", "static/shaders/default.fs");
    m_Shader->Bind();
    // m_Shader->SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);

    m_Texture = std::make_unique<Texture>("static/textures/brick.png");
    m_Shader->SetUniform1i("u_Texture", 0);
  };
  TestCamera::~TestCamera(){};

  void TestCamera::OnUpdate(float deltaTime){};

  void TestCamera::OnRender()
  {
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    Renderer renderer;
    m_Texture->Bind();

    double time = glfwGetTime();

    if (time - m_Time >= 1.0f / 60.0f)
    {
      m_Rotation += 1.0f;
      m_Time = time;
    }

    {
      // glm::mat4 mvpMatrix = m_ProjectionMatrix * m_ViewMatrix * modelMatrixA; // must be in reverse order. matrix multiplication is _not_ commutitive
      glm::mat4 modelMatrix = glm::mat4(1.0f);
      m_Camera.Inputs();
      m_Camera.Matrix(45.0f, 0.1f, 100.0f, *m_Shader, "u_CameraMatrix");

      // Assigns different transformations to each matrix
      modelMatrix = glm::rotate(modelMatrix, glm::radians(m_Rotation), glm::vec3(0.0f, 1.0f, 0.0f));
      // view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
      // proj = glm::perspective(glm::radians(45.0f), (float)WINDOW.width / WINDOW.height, 0.1f, 100.0f);

      // m_Shader->Bind();
      // m_Shader->SetUniformMat4f("u_Projection", proj);
      m_Shader->SetUniformMat4f("u_Model", modelMatrix);
      // m_Shader->SetUniformMat4f("u_View", view);
      // m_Shader->SetUniformMat4f("u_MVP", mvpMatrix);
      // m_Shader->SetUniform4f("u_Color", 0.32f, 0.78f, 0.7f, 1.0f);

      renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
  };

  void TestCamera::OnImGuiRender(){
      // ImGui::SliderFloat("X##a", &m_Translation.x, 0.0f, (float)WINDOW.width);
      // ImGui::SliderFloat("Y##a", &m_Translation.y, 0.0f, (float)WINDOW.height);
      // ImGui::SliderFloat("Z##a", &m_Translation.z, -100.0f, 0.1f);
  };
}