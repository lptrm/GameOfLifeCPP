#pragma once

#include "InstanceBuffer.h"
#include "RendererAPI.h"

class RenderCommand {
public:
  inline static void SetClearColor(const glm::vec4 &color) {
    s_RendererAPI->SetClearColor(color);
  }

  inline static void Clear() { s_RendererAPI->Clear(); }

  inline static void
  DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray,
              const std::shared_ptr<Shader> &shader) {
    s_RendererAPI->DrawIndexed(vertexArray, shader);
  }
  inline static void
  DrawInstanced(const std::shared_ptr<VertexArray> &vertexArray,
                const std::shared_ptr<Shader> &shader,
                const std::shared_ptr<InstanceBuffer> &instanceBuffer,
                glm::mat4 &u_MVP, const unsigned int count) {
    s_RendererAPI->DrawInstanced(vertexArray, shader, instanceBuffer, u_MVP,
                                 count);
  }

private:
  static RendererAPI *s_RendererAPI;
};
