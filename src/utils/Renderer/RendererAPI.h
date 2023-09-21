#pragma once

#include "InstanceBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <glm/glm.hpp>
#include <memory>
class RendererAPI {
public:
  enum class API { None = 0, OpenGL = 1 };

public:
  virtual void SetClearColor(const glm::vec4 &color) = 0;
  virtual void Clear() = 0;
  virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray,
                           const std::shared_ptr<Shader> &shader) = 0;
  virtual void DrawQuad(const std::shared_ptr<VertexArray> &vertexArray,
                        const std::shared_ptr<Shader> &shader, glm::mat4 &u_MVP,
                        const unsigned int count) = 0;
  virtual void
  DrawInstanced(const std::shared_ptr<VertexArray> &vertexArray,
                const std::shared_ptr<Shader> &shader,
                const std::shared_ptr<InstanceBuffer> &instanceBuffer,
                glm::mat4 &u_MVP, const unsigned int count) = 0;
  inline static API GetAPI() { return s_API; };

private:
  static API s_API;
};
