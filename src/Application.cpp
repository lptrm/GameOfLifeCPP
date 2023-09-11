#include "Application.h"
#include "ApplicationEvent.h"
#include "Event.h"
#include "KeyEvent.h"
#include "LayerStack.h"
#include "Layer_ImGui.h"
#include "Layer_Test.h"
#include "Layer_Universe.h"
#include "MouseEvent.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Window.h"
#include <iostream>
#include <memory>
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
std::unique_ptr<LayerStack> Application::m_LayerStack = nullptr;
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
  m_LayerStack = std::make_unique<LayerStack>();
};
int main(void) {

  {
    Application *app = new Application();
    // app->GetWindow().SetSize(1024, 1024);
    app->GetWindow().SetTitle("Game of Life");
    app->GetWindow().SetVSync(true);
    app->GetWindow().SetFullscreen(false);
    app->GetWindow().SetEventCallback(app->OnEvent);
    UniverseLayer *ul = new UniverseLayer(1024, 1024, 0.5, 0.5f, 128, 64);
    ImGuiLayer *il = new ImGuiLayer();
    TestLayer *tl = new TestLayer();

    app->GetLayerStack().PushLayer(ul);
    // app->GetLayerStack().PushLayer(tl);
    app->GetLayerStack().PushLayer(il);

    while (!glfwWindowShouldClose(app->GetWindow().GetNativeWindow())) {
      float time = (float)glfwGetTime();
      float deltaTime = time - app->m_LastFrameTime;
      app->m_LastFrameTime = time;
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

      glClear(GL_COLOR_BUFFER_BIT);
      for (auto &layer : app->GetLayerStack()) {
        layer->OnUpdate(deltaTime);
      }
      il->Begin();
      for (auto &layer : app->GetLayerStack()) {
        layer->OnImGuiRender();
      }
      il->End();

      app->GetWindow().OnUpdate();

    } // Cleanup
    app->GetLayerStack().PopLayer(ul);
    app->GetLayerStack().PopLayer(il);
    app->GetLayerStack().PopLayer(tl);
  }
  Window::ReleaseInstance();
  return 0;
}
