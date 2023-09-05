#include "Layer_Universe.h"
#include "Event.h"
#include "GLFW/glfw3.h"
#include <cstdint>
#include <iostream>

void UniverseLayer::OnAttach() {
  // // Initialize objects using dynamic memory allocation

  float screenWidth = 1280.0f;
  float screenHeight = 720.0f;
  // Initialize the camera controller
  m_CameraController = new GLCore::Utils::OrthographicCameraController(
      screenWidth / screenHeight, // Set your aspect ratio here
      false                       // Set to true if you want rotation
  );
  glm::mat4 projectionMatrix =
      glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
  glm::mat4 viewMatrix =
      glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(
      modelMatrix, glm::vec3(2.0f, 4.0f, 1.0f)); // Scale by 2 in X and Y
  *m_Mvp = projectionMatrix * viewMatrix * modelMatrix;

  m_Shader = new Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");
  unsigned int width = 128;
  unsigned int height = 64;
  float vertexWidth = 1.0f / width;
  // float vertexWidth = 10;
  float vertexHeight = 1.0f / height;
  // float vertexHeight = 10;
  float vertices[] = {0.0f,        0.0f,         0.0f,         0.0f,
                      vertexWidth, 0.0f,         vertexHeight, vertexWidth,
                      0.0f,        vertexHeight, 0.0f,         0.0f};

  m_Va = new VertexArray();
  m_Va->Bind();

  m_Vb = new VertexBuffer(vertices, 4 * 3 * sizeof(float));

  m_Layout = new VertexBufferLayout();
  m_Layout->Push<float>(3);

  m_Va->AddBuffer(*m_Vb, *m_Layout);

  GLuint indices[] = {0, 1, 2, 2, 3, 0};
  m_Ib = new IndexBuffer(indices, 6);

  // Initialize Universe
  m_Universe = new Universe(width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if ((i * 8 + j) % 2 == 0) {
        m_Universe->setAlive(j, i);
      }
      m_Universe->getCellInstance()[i * width + j].position =
          glm::vec3(j * vertexWidth, i * vertexHeight, 0.0f);
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

  m_Shader->SetUniformMat4f(
      "u_MVP", m_CameraController->GetCamera().GetViewProjectionMatrix());
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
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  double currentTime = glfwGetTime();
  double deltaTime = currentTime - m_LastTime;
  if (deltaTime >= m_GenerationTime) {
    m_Universe->update();
    m_LastTime = currentTime;
  }

  // Render using the initialized objects
  m_Shader->Bind();
  m_CameraController->OnUpdate(deltaTime);
  m_Shader->SetUniformMat4f(
      "u_MVP", m_CameraController->GetCamera().GetViewProjectionMatrix());
  // Print each row of the matrix
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout
          << m_CameraController->GetCamera().GetViewProjectionMatrix()[i][j]
          << " ";
    }
    std::cout << std::endl;
  }
  m_InstanceBuffer->UpdateInstanceData(m_Universe->getCellInstance().data(),
                                       m_Universe->getCellInstance().size() *
                                           sizeof(Universe::CellInstance));
  GLCALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 64 * 64));
}

void UniverseLayer::OnEvent(GLCore::Event &e) {
  m_CameraController->OnEvent(e);
}
