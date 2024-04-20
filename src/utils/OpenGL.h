/*
  OpenGL.h
  Created: April 15, 2024
*/

#pragma once
#include "globals.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__,__LINE__))

void GLClearErrors();
bool GLLogCall(const char *function, const char *file, int line);
std::string ParseGLFWKeyToName(int key);

void OnCursorPosition(GLFWwindow *window, double xpos, double ypos);
void OnCursorFocusChange(GLFWwindow *window, int entered);
void OnMouseButtonStatusChange(GLFWwindow *window, int button, int action, int mods);
void OnMouseScroll(GLFWwindow *window, double xoffset, double yoffset);
void OnKeyboardStatusChange(GLFWwindow *window, int key, int scancode, int action, int mods);
void OnWindowSizeChange(GLFWwindow* window, int width, int height);
