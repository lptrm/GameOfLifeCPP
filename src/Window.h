#include "GLFW/glfw3.h"
#include <string>
#pragma once

class Window {
  GLFWwindow *m_Window;
  std::string m_Title;
  unsigned int m_Width;
  unsigned int m_Height;
  bool m_VSync;
  bool m_Fullscreen;
  static void glfw_error_callback(int error, const char *description);

public:
  Window(const int width, const int height, const std::string &title);
  ~Window();
  void OnUpdate();

  inline unsigned int GetWidth() const { return m_Width; }
  inline unsigned int GetHeight() const { return m_Height; }
  inline bool GetVSync() const { return m_VSync; }
  inline bool GetFullscreen() const { return m_Fullscreen; }
  inline void SetVSync(bool vsync) { m_VSync = vsync; }
  inline void SetFullscreen(bool fullscreen) { m_Fullscreen = fullscreen; }
  inline GLFWwindow *GetWindow() const { return m_Window; }
};
