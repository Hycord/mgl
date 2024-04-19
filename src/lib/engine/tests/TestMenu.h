/*
  TestMenu.h
  Created: April 18, 2024
*/

#pragma once

#include "Test.h"
#include <vector>
#include <functional>
#include <string>
#include <iostream>

namespace test
{
    class TestMenu : public Test
    {
    public:
        TestMenu(Test *&currentTestPointer);

        // void OnUpdate(float deltaTime) override;
        // void OnRender() override;
        void OnImGuiRender() override;

        template <typename T>
        void RegisterTest(const std::string &name)
        {
            m_Tests.push_back(std::make_pair(name, []()
                                             { return new T(); }));
        }

    private:
        Test *&m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
    };
}