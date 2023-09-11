#pragma once

#include "LayerStack.h"
#include "Window.h"
#include <memory>
class Application {
  static Window *m_Window;
  static std::unique_ptr<LayerStack> m_LayerStack;

public:
  Application();
  ~Application();
  static void OnEvent(GLCore::Event &e);

  float m_LastFrameTime = 0.0f;
  inline static Window &GetWindow() { return *m_Window; }
  inline static LayerStack &GetLayerStack() { return *m_LayerStack; }
};
