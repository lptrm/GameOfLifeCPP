#pragma once
#include "RenderCommand.h"
#include "utils/Renderer/RendererAPI.h"

class Renderer2D {
public:
  static void BeginScene();
  static void EndScene();
  static void Submit(const std::shared_ptr<VertexArray> &vertexArray);
  inline static RendererAPI::API GetAPI() { return GetAPI(); };
};
