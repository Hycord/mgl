/*
  VertexArray.h
  Created: April 15, 2024
*/

#pragma once
#include "../Buffer/VertexBuffer.h"
#include "../Buffer/VertexBufferLayout.h"


class VertexArray
{
private:
    unsigned int m_RendererId;
public:
    VertexArray(/* args */);
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);


    void Bind() const;
    void Unbind() const;  
};

