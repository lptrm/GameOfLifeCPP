#include "Renderer.h"
#include "InstanceBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <iostream>

void GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool GLLogCall(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    std::cerr << "[OpenGL Error] (" << error << "): " << function << " " << file
              << ":" << line << std::endl;
    return false;
  }
  return true;
}
void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT); }
void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib,
                    const InstanceBuffer &instncb, const Shader &shader) const {
  shader.Bind();
  va.Bind();
  ib.Bind();
  GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
