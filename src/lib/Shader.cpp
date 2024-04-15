/*
  Shader.cpp
  Created: April 15, 2024
*/

#include "Shader.h"

#include "../utils/String.h"


ShaderProgramSource ParseShader(const std::string &data)
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

static unsigned int CompileShader(unsigned int type, const std::string &source)
{

    unsigned int id = glCreateShader(type);

    const char *src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char *message = (char *)alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);

        std::string typeName = type == GL_VERTEX_SHADER ? "vertex" : "fragment";

        std::cout << "[SHADER ERROR]: Failed to compile " << typeName << " shader \n[" << typeName << " " << repeat("-", 10 - typeName.length()) << ">]: ";
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int programId = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programId, vs);
    glAttachShader(programId, fs);

    glLinkProgram(programId);
    glValidateProgram(programId);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return programId;
}