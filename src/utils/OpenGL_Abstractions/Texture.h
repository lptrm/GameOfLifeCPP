#pragma once

#include "Renderer.h"
#include <string>
class Texture {
private:
  unsigned int m_RendererID;
  std::string m_FilePath;
  unsigned char *m_LocalBuffer;
  int m_Width, m_Height, m_BPP;

public:
  Texture(const std::string &path);
  ~Texture();
  // slot 0 per default but other values may be passed
  // a modern GPU may have 32 slots whilst mobile GPUs may have 8 slots for
  // textures
  void Bind(unsigned int slot = 0) const;
  void Unbind() const;
  inline int GetWidth() const { return m_Width; }
  inline int GetHeight() const { return m_Height; }
};
