/*
  Camera.cpp
  Created: April 21, 2024
*/

#include "Camera.h"

Camera::Camera(const int &width, const int &height, const glm::vec3 &position)
    : m_Position(position),
      m_Width(width),
      m_Height(height),
      m_Orientation(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
      m_Speed(0.1f),
      m_Sensitivity(0.1f),
      m_FirstClick(false)
{
}

Camera::~Camera()
{
}

void Camera::Matrix(const float &FOVDegree, const float &nearPlane, const float &farPlane, Shader &shader, const char *uniform)
{

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
    projection = glm::perspective(glm::radians(FOVDegree), (float)(m_Width / m_Height), nearPlane, farPlane);

    shader.Bind();
    shader.SetUniformMat4f(uniform, projection * view);
}   
void Camera::Inputs()
{
    if (KEYS.active.find("W") != KEYS.active.end())
    {
        m_Position += m_Speed * m_Orientation;
    }
    if (KEYS.active.find("A") != KEYS.active.end())
    {
        m_Position += m_Speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
    }
    if (KEYS.active.find("S") != KEYS.active.end())
    {
        m_Position += m_Speed * -m_Orientation;
    }
    if (KEYS.active.find("D") != KEYS.active.end())
    {
        m_Position += m_Speed * glm::normalize(glm::cross(m_Orientation, m_Up));
    }

    if (KEYS.active.find("SPACE") != KEYS.active.end())
    {
        m_Position += m_Speed * m_Up;
    }

    if (KEYS.active.find("LEFT_SHIFT") != KEYS.active.end())
    {
        m_Position += m_Speed * -m_Up;
    }

    if (KEYS.active.find("LEFT_CONTROL") != KEYS.active.end())
    {
        m_Speed = 0.4f;
    }
    else
        m_Speed = 0.1f;

    static glm::vec3 initialOrientation = m_Orientation;
    if (MOUSE.dragging)
    {

        float rotx = m_Sensitivity * MOUSE.dragOffset.x;
        float roty = m_Sensitivity * MOUSE.dragOffset.y;

        glm::vec3 rightVec = glm::cross(m_Orientation, m_Up);

        m_Orientation = glm::rotate(initialOrientation, glm::radians(-rotx), m_Up);
        m_Orientation = glm::rotate(m_Orientation, glm::radians(-roty), rightVec);

        if (WINDOW.glwindow != nullptr)
        {
            float centerX = WINDOW.width / 2.0f;
            float centerY = WINDOW.height / 2.0f;
            GLCall(glfwSetCursorPos(WINDOW.glwindow, centerX, centerY));
        }
    }
    else
    {
        initialOrientation = m_Orientation;
    }
}