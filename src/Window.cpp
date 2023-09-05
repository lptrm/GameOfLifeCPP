#include "Window.h"
#include "ApplicationEvent.h"
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
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

void Window::SetSize(unsigned int width, unsigned int height) {
  m_Data.Width = width;
  m_Data.Height = height;
  glfwSetWindowSize(m_Window, m_Data.Width, m_Data.Height);
}

void Window::SetTitle(const std::string &title) {
  m_Data.Title = title;
  glfwSetWindowTitle(m_Window, m_Data.Title.c_str());
}

void Window::SetVSync(bool vsync) {
  m_Data.VSync = vsync;
  glfwSwapInterval(m_Data.VSync ? 1 : 0);
}

void Window::SetFullscreen(bool fullscreen) {
  m_Data.Height = fullscreen;
  // Implement fullscreen/windowed mode switching logic here
}
Window::Window() {
  m_Data.Title = "Game of Life";
  m_Data.Width = 1280;
  m_Data.Height = 720;
  m_Data.VSync = true;
  m_Data.Fullscreen = false;

  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(),
                              nullptr, nullptr);
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
  if (m_Data.VSync) {
    glfwSwapInterval(1);
  }

  std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

  // Set GLFW callbacks
  glfwSetWindowUserPointer(m_Window, &m_Data);
  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        GLCore::WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });
  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode,
                                  int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    switch (action) {
    case GLFW_PRESS: {
      GLCore::KeyPressedEvent event(key, 0);
      data.EventCallback(event);
      break;
    }
    case GLFW_RELEASE: {
      GLCore::KeyReleasedEvent event(key);
      data.EventCallback(event);
      break;
    }
    case GLFW_REPEAT: {
      GLCore::KeyPressedEvent event(key, 1);
      data.EventCallback(event);
      break;
    }
    }
  });
  glfwSetCharCallback(m_Window, [](GLFWwindow *window, uint32_t keycode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    GLCore::KeyTypedEvent event(keycode);
    data.EventCallback(event);
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
          GLCore::MouseButtonPressedEvent event(button);
          data.EventCallback(event);
          break;
        }
        case GLFW_RELEASE: {
          GLCore::MouseButtonReleasedEvent event(button);
          data.EventCallback(event);
          break;
        }
        }
      });

  glfwSetScrollCallback(
      m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        GLCore::MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
      });

  glfwSetCursorPosCallback(
      m_Window, [](GLFWwindow *window, double xPos, double yPos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        GLCore::MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
      });
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
