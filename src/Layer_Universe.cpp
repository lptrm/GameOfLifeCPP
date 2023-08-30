#include "Layer_Universe.h"
#include "GLFW/glfw3.h"

void UniverseLayer::OnAttach() {
  // // Initialize objects using dynamic memory allocation
  glm::mat4 projectionMatrix = glm::ortho(0.0, 1024.0, 0.0, 768.0, -1.0, 1.0);
  glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(
      modelMatrix, glm::vec3(2.0f, 2.0f, 1.0f)); // Scale by 2 in X and Y
  *m_Mvp = projectionMatrix * viewMatrix * modelMatrix;

  m_Shader = new Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");

  // Set up vertex array and buffers
  float vertices[] = {0.0f,  0.0f,  0.0f, 0.f,   10.0f, 0.0f,
                      10.0f, 10.0f, 0.0f, 10.0f, 0.0f,  0.0f};
  m_Va = new VertexArray();
  m_Va->Bind();

  m_Vb = new VertexBuffer(vertices, 4 * 3 * sizeof(float));

  m_Layout = new VertexBufferLayout();
  m_Layout->Push<float>(3);

  m_Va->AddBuffer(*m_Vb, *m_Layout);

  GLuint indices[] = {0, 1, 2, 2, 3, 0};
  m_Ib = new IndexBuffer(indices, 6);

  // Initialize Universe
  m_Universe = new Universe(64, 64);
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      if ((i * 8 + j) % 2 == 0) {
        m_Universe->setAlive(j, i);
      }
      m_Universe->getCellInstance()[i * 64 + j].position =
          glm::vec3(j * 10, 768 - (i * 10), 0.0f);
    }
  }

  // Set up InstanceBuffer and InstanceBufferLayout
  m_InstanceBuffer = new InstanceBuffer(
      m_Universe->getCellInstance().data(),
      sizeof(Universe::CellInstance) * m_Universe->getCellInstance().size());
  m_InstanceLayout = new InstanceBufferLayout();
  m_InstanceLayout->Push<float>(3);
  m_InstanceLayout->Push<float>(3);
  m_InstanceBuffer->addAttributePointer(*m_InstanceLayout);

  m_Shader->SetUniformMat4f("u_MVP", *m_Mvp);
  // Set initial timestamp
  m_LastTime = glfwGetTime();
  m_GenerationTime = 0.5;
}

void UniverseLayer::OnDetach() {
  // Cleanup that you may want to do when the layer is detached
  // Release allocated memory in the destructor
  delete m_Mvp;
  delete m_Shader;
  delete m_Va;
  delete m_Vb;
  delete m_Layout;
  delete m_Ib;
  delete m_InstanceBuffer;
  delete m_InstanceLayout;
  delete m_Universe;
}

void UniverseLayer::OnUpdate(const double timeStamp) {
  double currentTime = glfwGetTime();
  double deltaTime = currentTime - m_LastTime;
  if (deltaTime >= m_GenerationTime) {
    m_Universe->update();
    m_LastTime = currentTime;
  }

  // Render using the initialized objects
  m_Shader->Bind();
  GLCALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
  GLCALL(glClear(GL_COLOR_BUFFER_BIT));
  m_InstanceBuffer->UpdateInstanceData(m_Universe->getCellInstance().data(),
                                       m_Universe->getCellInstance().size() *
                                           sizeof(Universe::CellInstance));
  GLCALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 64 * 64));
}

void UniverseLayer::OnEvent() {
  // Handle events if needed
}
