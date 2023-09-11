#include "Layer_Universe.h"
#include "Event.h"
#include "GLFW/glfw3.h"
#include "Input.h"
#include "OrthographicCamera.h"
#include "OrthographicCameraController.h"
#include "Renderer2D.h"
#include "Window.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "imgui_impl_opengl3.h"
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
UniverseLayer::~UniverseLayer() {}
void UniverseLayer::OnAttach() {

  m_CameraController =
      std::make_shared<GLCore::Utils::OrthographicCameraController>(
          m_ScreenWidth / m_ScreenHeight, true);

  m_Shader = std::make_shared<Shader>(
      "/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");

  float vertices[] = {0.0f, 0.0f, 0.0f,           m_VertexWidth,
                      0.0f, 0.0f, m_VertexWidth,  m_VertexHeight,
                      0.0f, 0.0f, m_VertexHeight, 0.0f};
  m_MatModel = glm::translate(
      m_MatModel, glm::vec3(m_Width * m_VertexWidth / -2.0f,
                            m_Height * m_VertexHeight / -2.0, 0.0f));
  m_Va = std::make_shared<VertexArray>();
  m_Va->Bind();

  m_Vb = std::make_shared<VertexBuffer>(vertices, 4 * 3 * sizeof(float));

  m_Layout = std::make_shared<VertexBufferLayout>();
  m_Layout->Push<float>(3);

  m_Va->AddBuffer(*m_Vb, *m_Layout);

  GLuint indices[] = {0, 1, 2, 2, 3, 0};
  m_Ib = std::make_shared<IndexBuffer>(indices, 6);

  m_Universe = std::make_shared<Universe>(m_Width, m_Height);
  for (int i = 0; i < m_Height; i++) {
    for (int j = 0; j < m_Width; j++) {
      m_Universe->getCellInstance()[i * m_Width + j].position =
          glm::vec3(j * m_VertexWidth, i * m_VertexHeight, 0.0f);
    }
  }
  FillRandomly(0.5f);

  m_InstanceBuffer = std::make_shared<InstanceBuffer>(
      m_Universe->getCellInstance().data(),
      sizeof(Universe::CellInstance) * m_Universe->getCellInstance().size());
  m_InstanceLayout = std::make_shared<InstanceBufferLayout>();
  m_InstanceLayout->Push<float>(4);
  m_InstanceLayout->Push<float>(3);
  m_InstanceBuffer->addAttributePointer(*m_InstanceLayout);
  u_MVP =
      m_CameraController->GetCamera().GetViewProjectionMatrix() * m_MatModel;
  m_Shader->SetUniformMat4f("u_MVP", u_MVP);
  m_LastTimeUniverse = 0.0f;

  m_GenerationTime = 0.5;
  Unbind();
}
void UniverseLayer::ResetUniverse() { m_Universe->ResetUniverse(); }
void UniverseLayer::FillRandomly(float density) {
  m_Universe->FillRandomly(density);
}
void UniverseLayer::OnDetach() { Unbind(); }

void UniverseLayer::OnUpdate(const float timeStamp) {
  if (!ImGui::GetIO().WantCaptureMouse) {
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      std::cout << "Left mouse button pressed" << std::endl;
      glm::mat4 viewProjectionMatrix =
          m_CameraController->GetCamera().GetViewProjectionMatrix();
      glm::vec4 screenCoords =
          glm::vec4(Input::GetMouseX(), Input::GetMouseY(), 0.0f, 1.0f);
      glm::vec4 worldCoords = glm::inverse(viewProjectionMatrix) * screenCoords;
      worldCoords /= worldCoords.w;
      std::cout << "World coords: " << worldCoords.x << ", " << worldCoords.y
                << std::endl;
      glm::vec3 rayOrigin = m_CameraController->GetCamera().GetPosition();
      glm::vec3 rayDirection = glm::normalize(
          glm::vec3(worldCoords.x, worldCoords.y, 0.0f) - rayOrigin);
      std::cout << "Ray origin: " << rayOrigin.x << ", " << rayOrigin.y << ", "
                << rayOrigin.z << std::endl;
      std::cout << "Ray direction: " << rayDirection.x << ", " << rayDirection.y
                << ", " << rayDirection.z << std::endl;
    }
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
      std::cout << "Right mouse button pressed" << std::endl;
    }
  }
  m_LastTimeUniverse += timeStamp;
  if (m_LastTimeUniverse >= m_GenerationTime) {
    m_Universe->update();
    m_LastTimeUniverse = 0.0f;
  }

  m_CameraController->OnUpdate(timeStamp);
  u_MVP =
      m_CameraController->GetCamera().GetViewProjectionMatrix() * m_MatModel;
  m_InstanceBuffer->UpdateInstanceData(m_Universe->getCellInstance().data(),
                                       m_Universe->getCellInstance().size() *
                                           sizeof(Universe::CellInstance));
  Renderer2D::DrawInstanced(m_Va, m_Shader, m_InstanceBuffer, u_MVP,
                            m_Universe->getCellInstance().size());
}

void UniverseLayer::OnEvent(GLCore::Event &e) {
  m_CameraController->OnEvent(e);
}
void UniverseLayer::Bind() {
  m_Va->Bind();
  m_Shader->Bind();
}
void UniverseLayer::Unbind() {
  m_Va->Unbind();
  m_Shader->Unbind();
}
void UniverseLayer::OnImGuiRender() {
  ImGuiIO &io = ImGui::GetIO();
  // 1. Show the big demo window (Most of the sample code is in
  // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
  // ImGui!).
  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair
  // to create a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and
                                   // append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can use
                                              // a format strings too)
    ImGui::Checkbox(
        "Demo Window",
        &show_demo_window); // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f,
                       1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit4("alive color", (float *)m_Universe->getColorAlive());
    ImGui::ColorEdit4("dead color", (float *)m_Universe->getColorDead());

    if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                 // widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window) {
    ImGui::Begin(
        "Another Window",
        &show_another_window); // Pass a pointer to our bool variable (the
                               // window will have a closing button that will
                               // clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }

  /*
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
*/
}
