
#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
  static Window &GetInstance();
  static void ReleaseInstance();

  void OnUpdate();
  inline GLFWwindow *GetNativeWindow() const { return m_Window; }
  inline unsigned int GetWidth() const { return m_Width; }
  inline unsigned int GetHeight() const { return m_Height; }
  inline bool GetVSync() const { return m_VSync; }
  inline bool GetFullscreen() const { return m_Fullscreen; }
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
