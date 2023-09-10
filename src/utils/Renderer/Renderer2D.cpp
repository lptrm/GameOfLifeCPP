#include "Renderer2D.h"
#include "RenderCommand.h"
void Renderer2D::BeginScene(){

};
void Renderer2D::EndScene(){};
void Renderer2D::DrawTest(const std::shared_ptr<VertexArray> &vertexArray,
                          const std::shared_ptr<Shader> &shader) {
  RenderCommand::DrawIndexed(vertexArray, shader);
}
void Renderer2D::DrawInstanced(
    const std::shared_ptr<VertexArray> &vertexArray,
    const std::shared_ptr<Shader> &shader,
    const std::shared_ptr<InstanceBuffer> &instanceBuffer, glm::mat4 &u_MVP,
    const unsigned int count) {
  RenderCommand::DrawInstanced(vertexArray, shader, instanceBuffer, u_MVP,
                               count);
}
