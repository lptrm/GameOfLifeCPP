#include "Layer_Universe.h"
#include "Event.h"
#include "GLFW/glfw3.h"
#include "Input.h"
#include "OrthographicCamera.h"
#include "OrthographicCameraController.h"
#include "Renderer2D.h"
#include "UniverseLayerInstance.h"
#include "Window.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "matrix.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <ostream>
UniverseLayer::UniverseLayer(float screenWidth, float screenHeight,
                             float vertexWidth, float vertexHeight,
                             unsigned int width, unsigned int height)
    : Layer("UniverseLayer"), m_ScreenWidth(screenWidth),
      m_ScreenHeight(screenHeight) {
  m_CameraController =
      std::make_shared<GLCore::Utils::OrthographicCameraController>(
          m_ScreenWidth / m_ScreenHeight, true);
  glm::mat4 mat = glm::mat4(1.0f);
  // UniverseLayer ul = UniverseLayer(vertexHeight, vertexWidth, width, height,
  //  this->GetViewProjectionMatrix() );
  m_UniverseInstances.assign(
      1, UniverseLayerInstance(
             vertexHeight, vertexWidth, width, height, 5.0,
             [this]() { return this->GetViewProjectionMatrix(); }));
}
UniverseLayer::~UniverseLayer() {}
void UniverseLayer::OnAttach() {}
void UniverseLayer::ResetUniverse() {}
void UniverseLayer::FillRandomly(float density) {}
void UniverseLayer::OnDetach() {}

void UniverseLayer::OnUpdate(const float timeStamp) {
  static float totalTimeUniverse = 0.0f;
  static int frameCountUniverse = 0;

  static float totalTimeDraw = 0.0f;
  static int frameCountDraw = 0;
  if (!ImGui::GetIO().WantCaptureMouse) {
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      glm::vec2 worldCoords = glm::vec2(
          (2.0f * (Input::GetMouseX() / Window::GetInstance().GetWidth())) -
              1.0f,
          1.0f - (2.0f *
                  (Input::GetMouseY() / Window::GetInstance().GetHeight())));
      m_UniverseInstances[0].UniverseIntersection(worldCoords);
    }
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
      std::cout << "Right mouse button pressed" << std::endl;
    }
  }
  // Measure time taken by Universe::update
  auto startUniverse = std::chrono::high_resolution_clock::now();
  for (auto &instance : m_UniverseInstances) {
    instance.GetLastTimeUniverse() += timeStamp;
    if (instance.GetLastTimeUniverse() >= instance.GetGenerationTime()) {
      instance.GetUniverse()->update();
      instance.GetLastTimeUniverse() = 0.0f;
    }
  }
  auto endUniverse = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> elapsedUniverse = endUniverse - startUniverse;

  // Measure time taken by Renderer2D::DrawInstanced
  auto startDraw = std::chrono::high_resolution_clock::now();
  m_CameraController->OnUpdate(timeStamp);

  for (auto &instance : m_UniverseInstances) {
    instance.Draw();
  }

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
void UniverseLayer::OnEvent(GLCore::Event &e) {
  m_CameraController->OnEvent(e);
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
    static int newWidth = 0, newHeight = 0;

    for (auto &instance : m_UniverseInstances) {
      ImGui::Begin("Test");
      instance.ImGuiRender();
      ImGui::End();
    }
    ImGui::Begin("Game Of Life"); // Create a window called "Hello, world!" and
                                  // append into it.
    ImGui::InputInt("Width", &newWidth);
    ImGui::InputInt("Height", &newHeight);
    if (ImGui::Button("Create New Universe")) {
      m_UniverseInstances.push_back(UniverseLayerInstance(
          1.0f, 1.0f, newWidth, newHeight, 5.0f,
          [this]() { return this->GetViewProjectionMatrix(); }));
    }
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
