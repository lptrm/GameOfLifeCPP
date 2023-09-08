#include "Renderer2D.h"
#include "RenderCommand.h"
void Renderer2D::BeginScene(){

};
void Renderer2D::EndScene(){};
void Renderer2D::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}
