#include "Application.h"
#include "ApplicationEvent.h"
#include "Event.h"
#include "KeyEvent.h"
#include "LayerStack.h"
#include "Layer_ImGui.h"
#include "Layer_Universe.h"
#include "MouseEvent.h"
#include "Window.h"
#include <iostream>
#include <stdio.h>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include "glad/glad.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
// test// Define and initialize the static members
Window *Application::m_Window = nullptr;
LayerStack *Application::m_LayerStack = nullptr;
static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
void Application::OnEvent(GLCore::Event &e) {

  GLCore::EventDispatcher dispatcher(e);

  // Dispatch the event and bind the OnWindowClose function to handle
  // WindowCloseEvent
  //    dispatcher.Dispatch<GLCore::WindowCloseEvent>(
  //        std::bind(&MyApplication::OnWindowClose, this,
  //        std::placeholders::_1)
  //    );
  for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();) {
    (*--it)->OnEvent(e);
    if (e.Handled)
      break;
  }
}
Application::Application() {
  m_Window = &Window::GetInstance();
  m_LayerStack = new LayerStack();
};
int main(void) {

  {
    Application *app = new Application();
    app->GetWindow().SetSize(1280, 720);
    app->GetWindow().SetTitle("Game of Life");
    app->GetWindow().SetVSync(true);
    app->GetWindow().SetFullscreen(false);
    app->GetWindow().SetEventCallback(app->OnEvent);
    UniverseLayer *ul = new UniverseLayer();
    ImGuiLayer *il = new ImGuiLayer();
    app->GetLayerStack().PushLayer(ul);
    app->GetLayerStack().PushLayer(il);
    // Implementation for OnAttach, if needed

    while (!glfwWindowShouldClose(app->GetWindow().GetNativeWindow())) {
      app->GetLayerStack().UpdateLayers(0.0);
      app->GetWindow().OnUpdate();
    } // Cleanup
    app->GetLayerStack().PopLayer(ul);
    app->GetLayerStack().PopLayer(il);

  } // for calling window destructor

  return 0;
}
