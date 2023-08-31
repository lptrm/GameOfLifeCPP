#include "LayerStack.h"
#include "Layer_ImGui.h"
#include "Layer_Universe.h"
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
    ls.PushLayer(ul);
    ls.PushLayer(il);
    // Implementation for OnAttach, if needed

    while (!glfwWindowShouldClose(Window::GetInstance().GetNativeWindow())) {

      ls.UpdateLayers(0.0);
      Window::GetInstance().OnUpdate();
    } // Cleanup
    ls.PopLayer(ul);
    ls.PopLayer(il);
  } // for calling window destructor

  return 0;
}
