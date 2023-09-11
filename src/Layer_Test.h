#pragma once

#include "Event.h"
#include "IndexBuffer.h"
#include "LayerStack.h"
#include "Shader.h"
#include "VertexArray.h"
#include "imgui.h"
#include <memory>

class TestLayer : public Layer {
  std::shared_ptr<VertexArray> m_Va;
  std::shared_ptr<VertexBuffer> m_Vb;
  std::shared_ptr<IndexBuffer> m_Ib;
  std::shared_ptr<VertexBufferLayout> m_Layout;
  std::shared_ptr<Shader> m_Shader;
  void Bind();
  void Unbind();

public:
  TestLayer() : Layer("TestLayer"){};
  ~TestLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const float timeStamp) override;
  virtual void OnEvent(GLCore::Event &e) override;
};
