#include "OpenGLRendererAPI.h"
#include "Renderer.h"
#include "glad/glad.h"
void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.r, color.g, color.b, color.a);
}
void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRendererAPI::DrawIndexed(
    const std::shared_ptr<VertexArray> &vertexArray,
    const std::shared_ptr<Shader> &shader) {
  vertexArray->Bind();
  shader->Bind();
  GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
  vertexArray->Unbind();
  shader->Unbind();
}
void OpenGLRendererAPI::DrawInstanced(
    const std::shared_ptr<VertexArray> &vertexArray,
    const std::shared_ptr<Shader> &shader,
    const std::shared_ptr<InstanceBuffer> &instanceBuffer, glm::mat4 &u_MVP,
    const unsigned int count) {
  vertexArray->Bind();
  shader->Bind();
  shader->SetUniformMat4f("u_MVP", u_MVP);
  GLCALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr,
                                 count));
  vertexArray->Unbind();
  shader->Unbind();
}
