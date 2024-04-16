/*
  Renderer.h
  Created: April 15, 2024
*/

#pragma once

#include "../data/Array/VertexArray.h"
#include "../data/Buffer/IndexBuffer.h"
#include "Shader.h"
#include "../../utils/OpenGL.h"

class Renderer
{
private:
    /* data */
public:
    Renderer(/* args */);
    ~Renderer();

    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};