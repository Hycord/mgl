/*
  Test.h
  Created: April 18, 2024
*/

#pragma once

#include "../../../utils/globals.h"

#include "../../../vendor/imgui/imgui.h"
#include "../../../vendor/imgui/imgui_impl_glfw.h"
#include "../../../vendor/imgui/imgui_impl_opengl3.h"

namespace test
{
  class Test
  {
  public:
    Test(){};
    virtual ~Test() {}

    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender() {}
  };


}