#include "OpenGLRendererAPI.h"
#include "glad/glad.h"
#include "utils/OpenGL_Abstractions/Renderer.h"
void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.r, color.g, color.b, color.a);
}
void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRendererAPI::DrawIndexed(
    const std::shared_ptr<VertexArray> &vertexArray) {
  vertexArray->Bind();
  GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
