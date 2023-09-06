#include "Layer_Universe.h"
#include "Event.h"
#include "GLFW/glfw3.h"
#include "OrthographicCameraController.h"
#include <cstdint>
#include <iostream>
UniverseLayer::UniverseLayer()
    : Layer("UniverseLayer"), m_CameraController(nullptr), m_Mvp(nullptr),
      m_Shader(nullptr), m_Va(nullptr), m_Vb(nullptr), m_Layout(nullptr),
      m_Ib(nullptr), m_InstanceBuffer(nullptr), m_InstanceLayout(nullptr),
      m_Universe(nullptr), m_LastTimeUniverse(0.0), m_GenerationTime(0.0) {
  // Initialize other members as needed
}
UniverseLayer::~UniverseLayer() {
  // Release allocated memory in the destructor
  delete m_CameraController; // If m_CameraController was allocated with new
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
void UniverseLayer::OnAttach() {
  // // Initialize objects using dynamic memory allocation

  float screenWidth = 1280.0f;
  float screenHeight = 720.0f;
  // Initialize the camera controller
  m_CameraController = new GLCore::Utils::OrthographicCameraController(
      screenWidth / screenHeight, // Set your aspect ratio here
      false                       // Set to true if you want rotation
  );

  m_Shader = new Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");
  m_Width = 1024;
  m_Height = 1024;
  // Calculate the aspect ratio
  // Determine the scaling factor based on the aspect ratio
  // Calculate the scaling factor based on the aspect ratio
  float vertexWidth, vertexHeight;
  if (m_Width >= m_Height) {
    // m_Width is greater or equal to m_Height
    vertexHeight = 1.0f / static_cast<float>(m_Height);
    vertexWidth = (static_cast<float>(m_Width) / static_cast<float>(m_Height)) /
                  static_cast<float>(m_Width);
  } else {
    vertexWidth = 1.0f / static_cast<float>(m_Width);
    vertexHeight =
        (static_cast<float>(m_Height) / static_cast<float>(m_Width)) /
        static_cast<float>(m_Height);
  }
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
  m_Universe = new Universe(m_Width, m_Height);
  for (int i = 0; i < m_Height; i++) {
    for (int j = 0; j < m_Width; j++) {
      if ((i * m_Width + j) % 2 == 0) {
        m_Universe->setAlive(j, i);
      }
      m_Universe->getCellInstance()[i * m_Width + j].position =
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
  m_LastTimeUniverse = glfwGetTime();
  // m_LastTimeFrame = m_LastTimeUniverse;

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
  double deltaTime = currentTime - m_LastTimeUniverse;
  if (deltaTime >= m_GenerationTime) {
    m_Universe->update();
    m_LastTimeUniverse = currentTime;
  }

  // Render using the initialized objects
  m_Shader->Bind();
  m_CameraController->OnUpdate(deltaTime);
  m_Shader->SetUniformMat4f(
      "u_MVP", m_CameraController->GetCamera().GetViewProjectionMatrix());
  m_InstanceBuffer->UpdateInstanceData(m_Universe->getCellInstance().data(),
                                       m_Universe->getCellInstance().size() *
                                           sizeof(Universe::CellInstance));
  GLCALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0,
                                 m_Width * m_Height));
}

void UniverseLayer::OnEvent(GLCore::Event &e) {
  m_CameraController->OnEvent(e);
}
