/*
  Shader.h
  Created: April 15, 2024
*/
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

ShaderProgramSource ParseShader(const std::string &data);
unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
static unsigned int CompileShader(unsigned int type, const std::string &source);
