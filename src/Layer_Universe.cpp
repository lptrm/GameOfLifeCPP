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
float UniverseLayer::totalTimeUniverse = 0.0f;
float UniverseLayer::totalTimeDraw = 0.0f;
int UniverseLayer::frameCountUniverse = 0;
int UniverseLayer::frameCountDraw = 0;
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
  m_UniverseInstances.push_back(UniverseLayerInstance(
      vertexHeight, vertexWidth, width, height, 1.0f,
      [this]() { return this->GetViewProjectionMatrix(); }));
}
UniverseLayer::~UniverseLayer() {}
void UniverseLayer::OnAttach() {}
void UniverseLayer::ResetUniverse() {}
void UniverseLayer::FillRandomly(float density) {}
void UniverseLayer::OnDetach() {}

void UniverseLayer::OnUpdate(const float timeStamp) {
  m_UniverseInstances.erase(std::remove_if(m_UniverseInstances.begin(),
                                           m_UniverseInstances.end(),
                                           [](UniverseLayerInstance &instance) {
                                             return instance.isGarbage;
                                           }),
                            m_UniverseInstances.end());
  if (!ImGui::GetIO().WantCaptureMouse) {
    if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
      glm::vec2 worldCoords = glm::vec2(
          (2.0f * (Input::GetMouseX() / Window::GetInstance().GetWidth())) -
              1.0f,
          1.0f - (2.0f *
                  (Input::GetMouseY() / Window::GetInstance().GetHeight())));
      for (auto it = m_UniverseInstances.rbegin();
           it != m_UniverseInstances.rend(); ++it) {
        UniverseLayerInstance &instance = *it;
        if (instance.UniverseIntersection(worldCoords)) {
          break;
        }
      }
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
  m_CameraController->OnUpdate(timeStamp);
  // Measure time taken by Renderer2D::DrawInstanced
  auto startDraw = std::chrono::high_resolution_clock::now();

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
}
void UniverseLayer::OnEvent(GLCore::Event &e) {
  m_CameraController->OnEvent(e);
}

void UniverseLayer::OnImGuiRender() {
  ImGuiIO &io = ImGui::GetIO();
  static int newWidth = 0, newHeight = 0;
  for (auto &instance : m_UniverseInstances) {
    instance.ImGuiRender();
  }

  if (ImGui::Begin("Configure A New Universe")) {
    ImGui::InputInt("Width", &newWidth);
    ImGui::InputInt("Height", &newHeight);
    float density = 0.5f;
    if (ImGui::Button("Create New Universe")) {
      m_UniverseInstances.push_back(UniverseLayerInstance(
          1.0f, 1.0f, newWidth, newHeight, density,
          [this]() { return this->GetViewProjectionMatrix(); }));
    }
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::Text("Application average Universe::update Time %.3f ms",
                1000.0f * totalTimeUniverse / frameCountUniverse);
    ImGui::Text("Application average Renderer2D::DrawInstanced Time %.3f ms",
                1000.0f * totalTimeDraw / (frameCountDraw));
    if (frameCountUniverse >= (1 << 31)) { // Print average every 100 frames
      frameCountUniverse = 0;
      totalTimeUniverse = 0.0f;
    }

    if (frameCountDraw >= (1 << 31)) { // Print average every 100 frames
      frameCountDraw = 0;
      totalTimeDraw = 0.0f;
    }
  }
  ImGui::End();
}
