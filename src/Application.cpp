#include "Shader.h"
#include "Universe.h"
#include "ext/matrix_transform.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <Logger.h>
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
  glm::mat4 viewMatrix =
      glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

  GLuint vaID;
  GLCALL(glCreateVertexArrays(1, &vaID));
  GLCALL(glBindVertexArray(vaID));

  float vertices[] = {0.0f,  0.0f,  0.0f, 0.f,   50.0f, 0.0f,
                      50.0f, 50.0f, 0.0f, 50.0f, 0.0f,  0.0f};

  GLuint vboid;
  GLCALL(glCreateBuffers(1, &vboid));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vboid));
  GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                      GL_STATIC_DRAW));

  GLCALL(glEnableVertexAttribArray(0));
  GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));

  GLuint indices[] = {0, 1, 2, 2, 3, 0};
  GLuint iboid;
  GLCALL(glCreateBuffers(1, &iboid));
  GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboid));
  GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                      GL_STATIC_DRAW));

  Shader shader = Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");
  shader.Bind();
  std::vector<glm::vec2> offsets = std::vector<glm::vec2>(64);

  Universe universe = Universe(8, 8);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      universe.setAlive(i, j);
      universe.getCellInstance()[i * j + j].position =
          glm::vec3(50, (7 - j) * 50, 0.0f);
      offsets[i * 8 + j] = glm::vec2(100 * i, (7 - j) * 100);
    }
  }

  GLuint instanceBuffer;
  GLCALL(glGenBuffers(1, &instanceBuffer));
  GLCALL(glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer));

  GLCALL(glBufferData(GL_ARRAY_BUFFER,
                      sizeof(Universe::CellInstance) *
                          universe.getCellInstance().size(),
                      universe.getCellInstance().data(), GL_STATIC_DRAW));
  // Set attribute pointers for instance data
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3),
                        (void *)0);
  glVertexAttribDivisor(
      1, 1); // This tells OpenGL to update this attribute for each instance

  shader.SetUniformMat4f("u_MVP", mvp);
  for (unsigned int i = 0; i < 64; i++) {
    shader.SetUniform2f("u_Offsets[" + std::to_string(i) + "]", offsets[i].x,
                        offsets[i].y);
  }
  GLCALL(glEnable(GL_BLEND));
  GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  double lastTime = glfwGetTime();
  double frameTime = 1.0;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {

    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastTime;

    if (deltaTime >= frameTime) {
      universe.update();
      universe.printGrid();
      // Start the Dear ImGui frame
      GLCALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
      GLCALL(glClear(GL_COLOR_BUFFER_BIT));

      shader.Bind();

      GLCALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 64));
      glfwPollEvents();
      glfwSwapBuffers(window);
      lastTime = currentTime;
    }
  }
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
