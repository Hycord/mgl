/*
  TestMenu.cpp
  Created: April 18, 2024
*/

#include "TestMenu.h"
#include "../../../vendor/imgui/imgui.h"

namespace test
{
    TestMenu::TestMenu(Test *&currentTestPointer)
        : m_CurrentTest(currentTestPointer), m_Tests()
    {
    }


    void TestMenu::OnImGuiRender()
    {
        for (auto &test : m_Tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                m_CurrentTest = test.second();
            }
        }
        if(ImGui::Button("Exit Debug Mode")){
            DEBUG = false;
        }
    }
}