#include "Window.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>
Window::Window(const int width, const int height, const std::string &title)
    : m_Width(width), m_Height(height), m_Title(title) {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
  if (!m_Window) {
    glfwTerminate();
    return;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(m_Window);

  // sync framerate with monitor refresh rate
  glfwSwapInterval(1);
  int version = gladLoadGL();
  if (version == 0) {
    std::cout << "Error" << std::endl;
    return;
  }
  std::cout << glGetString(GL_VERSION) << std::endl;
  /* Make the window's context current */
  glfwMakeContextCurrent(m_Window);
};
Window::~Window() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
};
void Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
};
void Window::glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
