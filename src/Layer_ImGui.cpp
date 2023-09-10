#include "Layer_ImGui.h"
#include "Renderer.h"
#include "Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include "glad/glad.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
void ImGuiLayer::OnAttach() {
  const char *glsl_version = "#version 130";
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(Window::GetInstance().GetNativeWindow(), true);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

void ImGuiLayer::OnDetach() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::Begin() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayer::End() { // Rendering
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(Window::GetInstance().GetNativeWindow(), &display_w,
                         &display_h);
  glViewport(0, 0, display_w, display_h);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
