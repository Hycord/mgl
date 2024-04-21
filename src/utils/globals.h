/*
  globals.h
  Created: April 15, 2024
*/

#pragma once

#include "glm/glm.hpp"
#include <map>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) \
  if ((!x))       \
    __builtin_trap();
// 0.32f, 0.78f, 0.7f, 1.0f

extern bool DEBUG;
struct Window {
  int width;
  int height;
  GLFWwindow *glwindow;
};
extern Window WINDOW;

struct Mouse
{
  glm::vec2 position;

  bool hovering;
  bool dragging;

  glm::vec2 dragOffset;
  glm::vec2 dragStart;
  glm::vec2 scrollOffset;

  bool leftHeld;
  bool midHeld;
  bool rightHeld;
};
extern Mouse MOUSE;

struct ModifierKeys
{
  bool control;
  bool alt;
  bool shift;

  bool super;
  bool capslock;
  bool numlock;
};

struct Keys
{
  std::map<std::string, bool> active;
  ModifierKeys mods;
};
extern Keys KEYS;