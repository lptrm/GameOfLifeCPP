#include "LayerStack.h"
#include "Layer_ImGui.h"
#include "Layer_Universe.h"
#include "Window.h"

#include <iostream>
#include <stdio.h>
#include <vector>

// test
static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
int main(void) {

  {

    Window::GetInstance().SetSize(1280, 720);
    Window::GetInstance().SetTitle("Game of Life");
    Window::GetInstance().SetVSync(true);
    Window::GetInstance().SetFullscreen(false);
    LayerStack ls = LayerStack();
    UniverseLayer *ul = new UniverseLayer();
    ImGuiLayer *il = new ImGuiLayer();
    il->OnAttach();
    ls.PushLayer(ul);

    while (!glfwWindowShouldClose((GLFWwindow *)&Window::GetInstance())) {

      ls.UpdateLayers(0.0);
      il->OnUpdate(0.0);
      Window::GetInstance().OnUpdate();
    }
    ls.PopLayer(ul);
  } // for calling window destructor

  return 0;
}
