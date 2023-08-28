#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "InstanceBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"
#include "Universe.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <stdio.h>
#include <vector>

// test
static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
int main(void) {

  GLFWwindow *window;
  const char *glsl_version = "#version 130";
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // sync framerate with monitor refresh rate
  glfwSwapInterval(1);
  int version = gladLoadGL();
  if (version == 0) {
    std::cout << "Error" << std::endl;
    return -1;
  }
  std::cout << glGetString(GL_VERSION) << std::endl;
  /* Make the window's context current */
  glfwMakeContextCurrent(window);

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
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // cutom Setup

  glm::mat4 projectionMatrix = glm::ortho(0.0, 1024.0, 0.0, 768.0, -1.0, 1.0);
  glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::scale(
      modelMatrix, glm::vec3(2.0f, 2.0f, 1.0f)); // Scale by 2 in X and Y
  glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

  VertexArray *va = new VertexArray();

  float vertices[] = {0.0f,  0.0f,  0.0f, 0.f,   10.0f, 0.0f,
                      10.0f, 10.0f, 0.0f, 10.0f, 0.0f,  0.0f};

  VertexBuffer *vb = new VertexBuffer(vertices, 4 * 3 * sizeof(float));
  VertexBufferLayout layout;
  layout.Push<float>(3);
  va->AddBuffer(*vb, layout);

  GLuint indices[] = {0, 1, 2, 2, 3, 0};

  IndexBuffer *ib = new IndexBuffer(indices, 6);

  Shader shader = Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");
  shader.Bind();

  Universe universe = Universe(64, 64);
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      if ((i * 8 + j) % 2 == 0) {
        universe.setAlive(j, i);
      }
      universe.getCellInstance()[i * 64 + j].position =
          glm::vec3(j * 10, 768 - (i * 10), 0.0f);
    }
  }
  InstanceBuffer instanceBuffer(universe.getCellInstance().data(),
                                sizeof(Universe::CellInstance) *
                                    universe.getCellInstance().size());
  InstanceBufferLayout iLayout;
  iLayout.Push<float>(3);
  iLayout.Push<float>(3);

  instanceBuffer.addAttributePointer(iLayout);
  shader.SetUniformMat4f("u_MVP", mvp);

  GLCALL(glEnable(GL_BLEND));
  GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  double lastTime = glfwGetTime();
  double frameTime = 0.1;
  /* Loop until the user closes
   * the window */
  while (!glfwWindowShouldClose(window)) {

    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;

    if (deltaTime >= frameTime) {
      universe.update();

      lastTime = currentTime;
    }
    shader.Bind();
    // Start the Dear ImGui
    // frame
    GLCALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    instanceBuffer.addAttributePointer(iLayout);
    instanceBuffer.UpdateInstanceData(universe.getCellInstance().data(),
                                      universe.getCellInstance().size() *
                                          sizeof(Universe::CellInstance));

    GLCALL(
        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 64 * 64));
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
