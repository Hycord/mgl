/*
  Camera.h
  Created: April 21, 2024
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "../draw/Shader.h"

#include "../../utils/globals.h"
#include "../../utils/OpenGL.h"

class Camera
{
private:
    /* data */
public:
    glm::vec3 m_Position,
        m_Orientation,
        m_Up;
    int m_Width, m_Height;
    float m_Speed,
        m_Sensitivity;
    bool m_FirstClick;

    Camera(const int &width, const int &height, const glm::vec3 &position);
    ~Camera();

    void Matrix(const float &FOVDegree, const float &nearPlane, const float &farPlane, Shader &shader, const char *uniform);
    void Inputs();
};

