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
  VertexBuffer *m_Vb;
  IndexBuffer *m_Ib;
  VertexBufferLayout *m_Layout;
  Shader *m_Shader;
  void Bind();
  void Unbind();

public:
  TestLayer() : Layer("TestLayer"){};
  ~TestLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const double timeStamp) override;
  virtual void OnEvent(GLCore::Event &e) override;
};
