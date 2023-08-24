#include "Shader.h"
#include "Universe.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <stdio.h>

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
  GLuint vaID;
  glCreateVertexArrays(1, &vaID);
  glBindVertexArray(vaID);

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
                      0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f};

  GLuint vboid;
  glCreateBuffers(1, &vboid);
  glBindBuffer(GL_ARRAY_BUFFER, vboid);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  GLuint indices[] = {0, 1, 2, 2, 3, 0};
  GLuint iboid;
  glCreateBuffers(1, &iboid);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboid);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  Shader shader =
      Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/basic.shader");
  shader.Bind();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
