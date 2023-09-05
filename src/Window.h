
#pragma once

#include "Event.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class Window {
public:
  using EventCallbackFn = std::function<void(GLCore::Event &)>;
  static Window &GetInstance();
  static void ReleaseInstance();

  void OnUpdate();
  inline GLFWwindow *GetNativeWindow() const { return m_Window; }
  inline unsigned int GetWidth() const { return m_Data.Width; }
  inline unsigned int GetHeight() const { return m_Data.Height; }
  inline bool GetVSync() const { return m_Data.VSync; }
  inline bool GetFullscreen() const { return m_Data.Fullscreen; }
  void SetSize(unsigned int width, unsigned int height);
  void SetTitle(const std::string &title);
  void SetVSync(bool vsync);
  void SetFullscreen(bool fullscreen);
  inline void SetEventCallback(const EventCallbackFn &callback) {
    m_Data.EventCallback = callback;
  };

private:
  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;
    bool Fullscreen;
    EventCallbackFn EventCallback;
  };

  WindowData m_Data;
  GLFWwindow *m_Window;
  static Window *m_Instance;

  Window();
  ~Window();
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  static void glfw_error_callback(int error, const char *description);
};
