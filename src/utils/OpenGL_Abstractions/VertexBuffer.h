#pragma once

class VertexBuffer {
private:
  unsigned int m_RendererID;

public:
  VertexBuffer(const void *data, int size);
  ~VertexBuffer();

  inline unsigned int getID() { return m_RendererID; }

  void Bind() const;
  void Unbind() const;
};
