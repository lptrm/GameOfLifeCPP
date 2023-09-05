#pragma once

#include "LayerStack.h"
#include "Window.h"
class Application {
  static Window *m_Window;
  static LayerStack *m_LayerStack;

public:
  Application();
  ~Application();
  static void OnEvent(GLCore::Event &e);

  inline static Window &GetWindow() { return *m_Window; }
  inline static LayerStack &GetLayerStack() { return *m_LayerStack; }
};
