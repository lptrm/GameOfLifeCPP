#include "Layer_Test.h"
#include "OpenGLRendererAPI.h"
#include "Renderer2D.h"
#include "VertexBufferLayout.h"
#include "utils/Renderer/RenderCommand.h"
#include <iostream>
#include <memory>

void TestLayer::OnAttach() { //  Implementation for OnAttach, if needed
  float positions[] = {
      -0.5f, -0.5f, // 0
      0.5f,  -0.5f, // 1
      0.5f,  0.5f,  // 2
      -0.5f, 0.5f   // 3
  };

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};
  m_Va = std::make_shared<VertexArray>();
  m_Vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
  m_Layout = new VertexBufferLayout();
  m_Layout->Push<float>(2);
  m_Va->AddBuffer(*m_Vb, *m_Layout);

  m_Shader =
      new Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/basic.shader");
  IndexBuffer *m_Ib = new IndexBuffer(indices, 6);
  Unbind();
}

void TestLayer::OnDetach() {}

void TestLayer::OnUpdate(const double timeStamp) {

  Bind();
  Renderer2D::Submit(m_Va);
  Unbind();
}

void TestLayer::OnEvent(GLCore::Event &e) {
  // Implementation for OnEvent, if needed
}
void TestLayer::Bind() { m_Shader->Bind(); }
void TestLayer::Unbind() {
  m_Va->Unbind();
  m_Shader->Unbind();
}
