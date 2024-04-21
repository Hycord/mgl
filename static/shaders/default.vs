#version 330 core

layout(location=0)in vec4 position;
layout(location=1)in vec2 texCoord;

out vec2 v_TexCoord;


uniform mat4 u_CameraMatrix;
uniform mat4 u_Model;

void main()
{
    gl_Position=u_CameraMatrix*u_Model*position;
    v_TexCoord=texCoord;
};