/*
  OpenGL.h
  Created: April 15, 2024
*/

#pragma once
#include "globals.h"

#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__,__LINE__))

void GLClearErrors();
bool GLLogCall(const char *function, const char *file, int line);