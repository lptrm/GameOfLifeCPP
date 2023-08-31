#pragma once
#include "Renderer.h"
#include <vector>

struct InstanceBufferElement {
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  inline static unsigned int GetSizeOfType(unsigned int type) {
    switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    case GL_UNSIGNED_BYTE:
      return 1;
    }
    ASSERT(false);
    return 0;
  }
};

class InstanceBufferLayout {
private:
  std::vector<InstanceBufferElement> m_Elements;
  unsigned int m_Stride;

public:
  InstanceBufferLayout() : m_Stride(0) {}

  template <typename T> void Push(unsigned int count);

  const std::vector<InstanceBufferElement> &GetElements() const {
    return m_Elements;
  }

  unsigned int GetStride() const { return m_Stride; }
};

// Template specialization for GL_FLOAT
template <> inline void InstanceBufferLayout::Push<float>(unsigned int count) {
  m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_Stride += InstanceBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

// Template specialization for GL_UNSIGNED_INT
template <>
inline void InstanceBufferLayout::Push<unsigned int>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += InstanceBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

// Template specialization for GL_UNSIGNED_BYTE
template <>
inline void InstanceBufferLayout::Push<unsigned char>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += InstanceBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}
