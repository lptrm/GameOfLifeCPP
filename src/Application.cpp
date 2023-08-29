#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "InstanceBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"
#include "Universe.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Window.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <stdio.h>
#include <vector>

// test
static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
int main(void) {

  const char *glsl_version = "#version 130";
  {
    Window window = Window(1024, 768, "Game of Life");

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
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
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

    Shader shader =
        Shader("/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");
    shader.Bind();

    Universe universe = Universe(128, 64);
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 128; j++) {
        if ((i * 128 + j) % 2 == 0) {
          universe.setAlive(j, i);
        }
        universe.getCellInstance()[i * 128 + j].position =
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

    double lastTime = glfwGetTime();
    double generationTime = 0.1;
    /* Loop until the user closes
     * the window */
    while (!glfwWindowShouldClose(window.GetWindow())) {

      double currentTime = glfwGetTime();
      double deltaTime = currentTime - lastTime;

      if (deltaTime >= generationTime) {
        universe.update();

        lastTime = currentTime;
      }
      shader.Bind();
      // Start the Dear ImGui
      // frame
      GLCALL(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
      GLCALL(glClear(GL_COLOR_BUFFER_BIT));
      instanceBuffer.UpdateInstanceData(universe.getCellInstance().data(),
                                        universe.getCellInstance().size() *
                                            sizeof(Universe::CellInstance));

      GLCALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0,
                                     128 * 64));
      window.OnUpdate();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  } // for calling window destructor

  return 0;
}
