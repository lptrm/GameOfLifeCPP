#include "Window.h"
#include "glad/glad.h"
#include <iostream>

Window *Window::m_Instance = nullptr;

Window &Window::GetInstance() {
  if (!m_Instance) {
    m_Instance = new Window();
  }
  return *m_Instance;
}

void Window::ReleaseInstance() {
  if (m_Instance) {
    delete m_Instance;
    m_Instance = nullptr;
  }
}

void Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

unsigned int Window::GetWidth() const { return m_Width; }

unsigned int Window::GetHeight() const { return m_Height; }

bool Window::GetVSync() const { return m_VSync; }

bool Window::GetFullscreen() const { return m_Fullscreen; }

void Window::SetSize(unsigned int width, unsigned int height) {
  m_Width = width;
  m_Height = height;
  glfwSetWindowSize(m_Window, m_Width, m_Height);
}

void Window::SetTitle(const std::string &title) {
  m_Title = title;
  glfwSetWindowTitle(m_Window, m_Title.c_str());
}

void Window::SetVSync(bool vsync) {
  m_VSync = vsync;
  glfwSwapInterval(m_VSync ? 1 : 0);
}

void Window::SetFullscreen(bool fullscreen) {
  m_Fullscreen = fullscreen;
  // Implement fullscreen/windowed mode switching logic here
}
Window::Window()
    : m_Width(800), m_Height(600), m_Title("Singleton Window"), m_VSync(false),
      m_Fullscreen(false) {
  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_Window =
      glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
  if (!m_Window) {
    glfwTerminate();
    std::cerr << "Failed to create GLFW window" << std::endl;
    return;
  }

  glfwMakeContextCurrent(m_Window);

  if (gladLoadGL() == 0) {
    std::cerr << "Failed to initialize Glad" << std::endl;
    return;
  }

  glfwMakeContextCurrent(m_Window);

  // Enable VSync
  if (m_VSync) {
    glfwSwapInterval(1);
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
  if (m_Window) {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
  }
}

void Window::glfw_error_callback(int error, const char *description) {
  std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}
