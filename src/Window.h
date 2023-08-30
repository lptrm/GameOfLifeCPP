
#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
  static Window &GetInstance();
  static void ReleaseInstance();

  void OnUpdate();
  unsigned int GetWidth() const;
  unsigned int GetHeight() const;
  bool GetVSync() const;
  bool GetFullscreen() const;
  void SetSize(unsigned int width, unsigned int height);
  void SetTitle(const std::string &title);
  void SetVSync(bool vsync);
  void SetFullscreen(bool fullscreen);

private:
  GLFWwindow *m_Window;
  std::string m_Title;
  unsigned int m_Width;
  unsigned int m_Height;
  bool m_VSync;
  bool m_Fullscreen;

  static Window *m_Instance;

  Window();
  ~Window();
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  static void glfw_error_callback(int error, const char *description);
};
