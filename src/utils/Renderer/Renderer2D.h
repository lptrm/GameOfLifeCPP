#pragma once
#include "InstanceBuffer.h"
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "fwd.hpp"
#include <memory>
class Renderer2D {
public:
  static void BeginScene();
  static void EndScene();
  static void DrawTest(const std::shared_ptr<VertexArray> &vertexArray,
                       const std::shared_ptr<Shader> &shader);
  static void
  DrawInstanced(const std::shared_ptr<VertexArray> &vertexArray,
                const std::shared_ptr<Shader> &shader,
                const std::shared_ptr<InstanceBuffer> &instanceBuffer,
                glm::mat4 &u_MVP, const unsigned int count);
  inline static RendererAPI::API GetAPI() { return GetAPI(); };
};
