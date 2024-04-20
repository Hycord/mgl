/*
  ImGUI.cpp
  Created: April 19, 2024
*/

#include "ImGUI.h"

void RenderFPS()
{
    ImGui::Text("%.1f FPS | %.3fms", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
}