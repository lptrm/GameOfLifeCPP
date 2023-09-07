#include "Layer_Universe.h"
#include "Event.h"
#include "GLFW/glfw3.h"
#include "OrthographicCamera.h"
#include "OrthographicCameraController.h"
#include "ext/matrix_transform.hpp"
#include <cstdint>
#include <iostream>
#include <ostream>
UniverseLayer::UniverseLayer(float screenWidth, float screenHeight,
                             float vertexWidth, float vertexHeight,
                             unsigned int width, unsigned int height)
    : Layer("UniverseLayer"), m_CameraController(nullptr),
      u_MVP(glm::mat4(1.0f)), m_MatModel(glm::mat4(1.0f)), m_Shader(nullptr),
      m_Va(nullptr), m_Vb(nullptr), m_Layout(nullptr), m_Ib(nullptr),
      m_InstanceBuffer(nullptr), m_InstanceLayout(nullptr), m_Universe(nullptr),
      m_LastTimeUniverse(0.0), m_GenerationTime(0.0),
      m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight),
      m_VertexWidth(vertexWidth), m_VertexHeight(vertexHeight), m_Width(width),
      m_Height(height) {}
UniverseLayer::~UniverseLayer() {
  // Release allocated memory in the destructor
  delete m_CameraController; // If m_CameraController was allocated with new
  delete m_Shader;
  delete m_Va;
  delete m_Vb;
  delete m_Layout;
  delete m_Ib;
  delete m_InstanceBuffer;
  delete m_InstanceLayout;
  delete m_Universe;
}
void UniverseLayer::OnAttach() {

  m_CameraController = new GLCore::Utils::OrthographicCameraController(
      m_ScreenWidth / m_ScreenHeight, true);

  m_Shader = new Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");

  float vertices[] = {0.0f, 0.0f, 0.0f,           m_VertexWidth,
                      0.0f, 0.0f, m_VertexWidth,  m_VertexHeight,
                      0.0f, 0.0f, m_VertexHeight, 0.0f};
  m_MatModel = glm::translate(
      m_MatModel, glm::vec3(m_Width * m_VertexWidth / -2.0f,
                            m_Height * m_VertexHeight / -2.0, 0.0f));
  m_Va = new VertexArray();
  m_Va->Bind();

  m_Vb = new VertexBuffer(vertices, 4 * 3 * sizeof(float));

  m_Layout = new VertexBufferLayout();
  m_Layout->Push<float>(3);

  m_Va->AddBuffer(*m_Vb, *m_Layout);

  GLuint indices[] = {0, 1, 2, 2, 3, 0};
  m_Ib = new IndexBuffer(indices, 6);

  m_Universe = new Universe(m_Width, m_Height);
  for (int i = 0; i < m_Height; i++) {
    for (int j = 0; j < m_Width; j++) {
      m_Universe->getCellInstance()[i * m_Width + j].position =
          glm::vec3(j * m_VertexWidth, i * m_VertexHeight, 0.0f);
    }
  }
  FillRandomly(0.5f);

  m_InstanceBuffer = new InstanceBuffer(
      m_Universe->getCellInstance().data(),
      sizeof(Universe::CellInstance) * m_Universe->getCellInstance().size());
  m_InstanceLayout = new InstanceBufferLayout();
  m_InstanceLayout->Push<float>(3);
  m_InstanceLayout->Push<float>(3);
  m_InstanceBuffer->addAttributePointer(*m_InstanceLayout);
  u_MVP =
      m_CameraController->GetCamera().GetViewProjectionMatrix() * m_MatModel;
  m_Shader->SetUniformMat4f("u_MVP", u_MVP);
  m_LastTimeUniverse = glfwGetTime();

  m_GenerationTime = 0.5;
  Unbind();
}
void UniverseLayer::ResetUniverse() { m_Universe->ResetUniverse(); }
void UniverseLayer::FillRandomly(float density) {
  m_Universe->FillRandomly(density);
}
void UniverseLayer::OnDetach() {
  Unbind();
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
  double deltaTime = currentTime - m_LastTimeUniverse;
  if (deltaTime >= m_GenerationTime) {
    m_Universe->update();
    m_LastTimeUniverse = currentTime;
  }

  Bind();
  m_CameraController->OnUpdate(deltaTime);
  u_MVP =
      m_CameraController->GetCamera().GetViewProjectionMatrix() * m_MatModel;
  m_Shader->SetUniformMat4f("u_MVP", u_MVP);
  m_InstanceBuffer->UpdateInstanceData(m_Universe->getCellInstance().data(),
                                       m_Universe->getCellInstance().size() *
                                           sizeof(Universe::CellInstance));
  GLCALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0,
                                 m_Width * m_Height));

  Unbind();
}

void UniverseLayer::OnEvent(GLCore::Event &e) {
  m_CameraController->OnEvent(e);
}
void UniverseLayer::Bind() {
  m_Va->Bind();
  m_Vb->Bind();
  m_Ib->Bind();
  m_Shader->Bind();
  m_InstanceBuffer->Bind();
}
void UniverseLayer::Unbind() {
  m_Va->Unbind();
  m_Vb->Unbind();
  m_Ib->Unbind();
  m_Shader->Unbind();
  m_InstanceBuffer->Unbind();
}
