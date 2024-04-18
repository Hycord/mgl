/*
  Texture.h
  Created: April 15, 2024
*/

#pragma once
#include <GL/glew.h>
#include <string>
#include "../../utils/OpenGL.h"
#include "stb/stb_image.h"

class Texture
{
private:
    /* data */
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string &path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetBPP() const { return m_BPP; }
};
