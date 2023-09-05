#include "InstanceBuffer.h"
#include "InstanceBufferLayout.h"
#include "Renderer.h"
#include "glm.hpp"
InstanceBuffer::InstanceBuffer(const void *data, unsigned int size) {
  GLCALL(glGenBuffers(1, &m_RendererID));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

  GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

InstanceBuffer::~InstanceBuffer() { GLCALL(glDeleteBuffers(1, &m_RendererID)); }

void InstanceBuffer::addAttributePointer(const InstanceBufferLayout &layout) {
  Bind();

  const auto &elements = layout.GetElements();
  unsigned int offset = 0;

  GLsizei stride = sizeof(glm::vec3) * 2;
  for (unsigned int i = 0; i < elements.size(); i++) {
    const auto &element = elements[i];
    GLCALL(glEnableVertexAttribArray(i + 1)); // Enable the vertex attribute
    // Set the vertex attribute pointer for instance data
    GLCALL(glVertexAttribPointer(i + 1, element.count, element.type, stride,
                                 layout.GetStride(), (const void *)offset));

    offset +=
        element.count * InstanceBufferElement::GetSizeOfType(element.type);

    GLCALL(glVertexAttribDivisor(
        i + 1,
        1)); // This tells OpenGL to update this attribute for each instance
  }
}
void InstanceBuffer::UpdateInstanceData(const void *data,
                                        unsigned int size) const {
  Bind();
  GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
}
void InstanceBuffer::Bind() const {
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void InstanceBuffer::Unbind() const {
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
