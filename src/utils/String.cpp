/*
  String.cpp
  Created: April 15, 2024
*/

#include "String.h"


std::string repeat(const std::string &input, unsigned num)
{
    std::string ret;
    ret.reserve(input.size() * num);
    while (num--)
        ret += input;
    return ret;
}