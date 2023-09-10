#pragma once

#include "InstanceBuffer.h"
#include "RendererAPI.h"
#include "VertexArray.h"
class OpenGLRendererAPI : public RendererAPI {
public:
  virtual void SetClearColor(const glm::vec4 &color) override;
  virtual void Clear() override;
  virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray,
                           const std::shared_ptr<Shader> &shader) override;
  virtual void
  DrawInstanced(const std::shared_ptr<VertexArray> &vertexArray,
                const std::shared_ptr<Shader> &shader,
                const std::shared_ptr<InstanceBuffer> &instanceBuffer,
                glm::mat4 &u_MVP, const unsigned int count) override;
};
