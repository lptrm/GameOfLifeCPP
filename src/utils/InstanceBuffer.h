#pragma once

class InstanceBufferLayout;

class InstanceBuffer {
private:
  unsigned int m_RendererID;

public:
  InstanceBuffer(const void *data, unsigned int size);
  ~InstanceBuffer();
  void UpdateInstanceData(const void *data, unsigned int size) const;
  void addAttributePointer(const InstanceBufferLayout &layout);
  void Bind() const;
  void Unbind() const;
};
