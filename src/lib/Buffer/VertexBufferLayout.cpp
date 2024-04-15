/*
  VertexBufferLayout.cpp
  Created: April 15, 2024
*/

#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(/* args */) : m_Stride(0), m_Elements()
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({count,
                          GL_UNSIGNED_INT,
                          GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template <>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({count,
                          GL_BYTE,
                          GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_BYTE) * count;
}
template <>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({count,
                          GL_FLOAT,
                          GL_FALSE});
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}
