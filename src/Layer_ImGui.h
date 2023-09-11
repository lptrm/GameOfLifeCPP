#pragma once

#include "Event.h"
#include "LayerStack.h"
#include "MouseEvent.h"
#include "imgui.h"

class ImGuiLayer : public Layer {

public:
  ImGuiLayer() : Layer("ImGuiLayer"){};
  ~ImGuiLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnEvent(GLCore::Event &e) override;
  bool OnMouseButtonPressedEvent(GLCore::MouseButtonPressedEvent &e);
  bool OnMouseScrolledEvent(GLCore::MouseScrolledEvent &e);
  void Begin();
  void End();
};
