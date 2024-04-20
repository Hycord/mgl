/*
  globals.cpp
  Created: April 19, 2024
*/

#include "globals.h"

bool DEBUG = false;
Mouse MOUSE = {
    .position = glm::vec2(-1.0f, -1.0f),
    .hovering = false,
    .dragging = false,
    .dragOffset = glm::vec2(-1.0f, -1.0f),
    .dragStart = glm::vec2(-1.0f, -1.0f),
    .scrollOffset = glm::vec2(0.0f, 0.0f),
    .leftHeld = false,
    .midHeld = false,
    .rightHeld = false};

Keys KEYS = {
    .active = std::map<std::string, bool>(),
    .mods = {
        .control = false,
        .alt = false,
        .shift = false,
        .super = false,
        .capslock = false,
        .numlock = false,
    }};

Window WINDOW = {1000, 800};