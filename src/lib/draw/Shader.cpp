/*
  Shader.cpp
  Created: April 15, 2024
*/

#include "Shader.h"
#include <iostream>

#include "../../utils/String.h"
#include "../../utils/OpenGL.h"
#include "../../utils/FileReader.h"

Shader::Shader(const std::string &filepath)
    : m_Filepath(filepath), m_RendererID(0), m_UniformLocationCache()
{
    std::string rawShader = ReadFile(m_Filepath);
    ShaderProgramSource shaders = Shader::ParseShader(rawShader);
    m_RendererID = Shader::CreateShader(shaders.VertexSource, shaders.FragmentSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
void Shader::SetUniform1f(const std::string name, float v0)
{
    GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniform1i(const std::string name, int v0)
{
    GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniformMat4f(const std::string name, const glm::mat4 matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string &name)
{

    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    m_UniformLocationCache[name] = location;

    if (location == -1)
    {
        std::cout << "[WARNING]: Useless uniform: " << name << " in " << m_Filepath << std::endl;
    }
    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string &data)
{
    std::istringstream stream(data);

    std::stringstream ss[2];

    std::string line;

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line, '\n'))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {

            ss[(int)type] << line << "\n"; // Already contains \n
        }
    }
    return {
        ss[0].str(),
        ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{

    GLCall(unsigned int id = glCreateShader(type));

    const char *src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char *message = (char *)alloca(length * sizeof(char));

        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::string typeName = type == GL_VERTEX_SHADER ? "vertex" : "fragment";

        std::cout << "[SHADER ERROR]: Failed to compile " << typeName << " shader \n[" << typeName << " " << repeat("-", 10 - typeName.length()) << ">]: ";
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    GLCall(unsigned int programId = glCreateProgram());

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(programId, vs));
    GLCall(glAttachShader(programId, fs));

    GLCall(glLinkProgram(programId));
    GLCall(glValidateProgram(programId));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return programId;
}
