/*
  OpenGL.cpp
  Created: April 15, 2024
*/

#include "OpenGL.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR)
		;
}

bool GLLogCall(const char *function, const char *file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OPENGL ERROR]: " << error << ": (" << function << ") "
				<< file << ":" << line << std::endl;
		return false;
	}
	return true;
}
