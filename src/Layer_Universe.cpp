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
#include "matrix.hpp"
#include <chrono>
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
      m_MatModel, glm::vec3(m_VertexWidth * m_Width * -0.5f,
                            m_VertexHeight * m_Height * -0.5f, 0.0f));
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
  m_GenerationTime = 5.0;
  Unbind();
}
void UniverseLayer::ResetUniverse() { m_Universe->ResetUniverse(); }
void UniverseLayer::FillRandomly(float density) {
  m_Universe->FillRandomly(density);
}
void UniverseLayer::OnDetach() { Unbind(); }

void UniverseLayer::OnUpdate(const float timeStamp) {
  static float totalTimeUniverse = 0.0f;
  static int frameCountUniverse = 0;

  static float totalTimeDraw = 0.0f;
  static int frameCountDraw = 0;
  if (!ImGui::GetIO().WantCaptureMouse) {
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      glm::vec2 intersectionPoint;
      if (UniverseIntersection(intersectionPoint)) {
        intersectionPoint = glm::inverse(

                                m_MatModel) *
                            glm::vec4(intersectionPoint, 0.0f, 1.0f);

        int row = (int)(intersectionPoint.y / m_VertexHeight);
        int col = (int)(intersectionPoint.x / m_VertexWidth);
        m_Universe->setAlive(col, row);
      } else {
        std::cout << "No intersection" << std::endl;
      }
    }
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
      std::cout << "Right mouse button pressed" << std::endl;
    }
  }
  // Measure time taken by Universe::update
  auto startUniverse = std::chrono::high_resolution_clock::now();
  m_LastTimeUniverse += timeStamp;
  if (m_LastTimeUniverse >= m_GenerationTime) {
    m_Universe->update();
    m_LastTimeUniverse = 0.0f;
  }
  auto endUniverse = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> elapsedUniverse = endUniverse - startUniverse;

  // Measure time taken by Renderer2D::DrawInstanced
  auto startDraw = std::chrono::high_resolution_clock::now();
  m_CameraController->OnUpdate(timeStamp);
  u_MVP =
      m_CameraController->GetCamera().GetViewProjectionMatrix() * m_MatModel;
  m_InstanceBuffer->UpdateInstanceData(m_Universe->getCellInstance().data(),
                                       m_Universe->getCellInstance().size() *
                                           sizeof(Universe::CellInstance));
  Renderer2D::DrawInstanced(m_Va, m_Shader, m_InstanceBuffer, u_MVP,
                            m_Universe->getCellInstance().size());
  auto endDraw = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> elapsedDraw = endDraw - startDraw;

  // Update and print performance statistics
  totalTimeUniverse += elapsedUniverse.count();
  frameCountUniverse++;
  totalTimeDraw += elapsedDraw.count();
  frameCountDraw++;

  if (frameCountUniverse >= 100) { // Print average every 100 frames
    std::cout << "Average Universe::update time: "
              << totalTimeUniverse / frameCountUniverse << " seconds"
              << std::endl;
    frameCountUniverse = 0;
    totalTimeUniverse = 0.0f;
  }

  if (frameCountDraw >= 100) { // Print average every 100 frames
    std::cout << "Average Renderer2D::DrawInstanced time: "
              << totalTimeDraw / frameCountDraw << " seconds" << std::endl;
    frameCountDraw = 0;
    totalTimeDraw = 0.0f;
  }
}
bool UniverseLayer::UniverseIntersection(glm::vec2 &intersectionPoint) {
  glm::mat4 viewProjectionMatrix =
      m_CameraController->GetCamera().GetViewProjectionMatrix();
  glm::vec4 screenCoords = glm::vec4(
      (2.0f * (Input::GetMouseX() / Window::GetInstance().GetWidth())) - 1.0f,
      1.0f - (2.0f * (Input::GetMouseY() / Window::GetInstance().GetHeight())),
      0.0f, 1.0f);
  glm::vec4 worldCoords = glm::inverse(viewProjectionMatrix) * screenCoords;
  worldCoords /= worldCoords.w;

  if (worldCoords.x < m_VertexWidth * m_Width * -0.5f ||
      worldCoords.x > m_VertexWidth * m_Width * 0.5f ||
      worldCoords.y < m_VertexHeight * m_Height * -0.5f ||
      worldCoords.y > m_VertexHeight * m_Height * 0.5f) {
    std::cout << "Out of bounds" << std::endl;
    return false;
  }
  intersectionPoint.x = worldCoords.x;
  intersectionPoint.y = worldCoords.y;
  return true;
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
    static float fillRandomly = 0.0f;
    static int counter = 0;

    ImGui::Begin("Game Of Life"); // Create a window called "Hello, world!" and
                                  // append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can use
                                              // a format strings too)
    ImGui::SliderFloat("time for generation (s)", &m_GenerationTime, 0.0f,
                       10.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("density(alive) after reset (s)", &fillRandomly, 0.0f,
                       1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    if (ImGui::Button("Reset Universe")) {
      m_Universe->ResetUniverse();
      FillRandomly(fillRandomly);
    } // Buttons return true when clicked
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
