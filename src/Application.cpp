#include "Universe.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

void printGrid(const Universe &universe) {
  for (int i = 0; i < universe.getSize(); i++) {
    int intIndex = i >> 5;
    int bitIndex = i & 31;
    int bitValue = (universe.getGameGrid()[intIndex] >> bitIndex) & 1;
    std::cout << bitValue << "";
    if ((i + 1) % universe.getWidth() == 0) {
      std::cout << std::endl;
    }
  }
}
int main(void) {
  GLFWwindow *window;

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

  int width = 64;
  int height = 64;

  Universe universe(width, height);
  std::cout << "Empty Grid:" << std::endl;
  printGrid(universe);

  // Set some cells as alive (you can modify this for testing)
  int aliveCells[] = {0, 1, 3, 4, 5, 6, 7, 8, 9, 55};
  for (int cell : aliveCells) {
    int intIndex = cell >> 5;
    int bitOffset = cell & 31;
    universe.getGameGrid()[intIndex] |=
        (1 << bitOffset); // Set the corresponding bit to 1
  }

  std::cout << "Initial Grid:" << std::endl;
  printGrid(universe);

  universe.update();

  std::cout << "Updated Grid:" << std::endl;
  printGrid(universe);

  universe.update();

  std::cout << "Updated Grid:" << std::endl;
  printGrid(universe);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
