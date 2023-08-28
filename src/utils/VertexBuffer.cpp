#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void *data, int size) {
  // generate buffer
  GLCALL(glGenBuffers(1, &m_RendererID));
  // bind buffer
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
  // set buffer data
  GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() { GLCALL(glDeleteBuffers(1, &m_RendererID)); }

void VertexBuffer::Bind() const {
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const { GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
