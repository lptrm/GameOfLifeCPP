#include "Layer_Test.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include <iostream>

void TestLayer::OnAttach() { //  Implementation for OnAttach, if needed
  /*
  float positions[] = {
      -0.5f, -0.5f, // 0
      0.5f,  -0.5f, // 1
      0.5f,  0.5f,  // 2
      -0.5f, 0.5f   // 3
  };

  unsigned int indices[] = {0, 1, 2, 2, 3, 0};
  m_Va = new VertexArray();
  m_Vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
  m_Layout = new VertexBufferLayout();
  m_Layout->Push<float>(2);
  m_Va->AddBuffer(*m_Vb, *m_Layout);

  m_Shader =
      new Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/basic.shader");
  IndexBuffer *m_Ib = new IndexBuffer(indices, 6);
  Unbind();
  */
}

void TestLayer::OnDetach() {}

void TestLayer::OnUpdate(const double timeStamp) {
  /*
    Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    Unbind();
    */
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);
}

void TestLayer::OnEvent(GLCore::Event &e) {
  // Implementation for OnEvent, if needed
}
void TestLayer::Bind() {
  m_Va->Bind();
  m_Vb->Bind();
  m_Shader->Bind();
}
void TestLayer::Unbind() {
  m_Va->Unbind();
  m_Vb->Unbind();
  m_Shader->Unbind();
}
