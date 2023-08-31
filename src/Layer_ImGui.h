#pragma once

#include "LayerStack.h"
#include "imgui.h"

class ImGuiLayer : public Layer {

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:
  ImGuiLayer() : Layer("ImGuiLayer"){};
  ~ImGuiLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const double timeStamp) override;
  virtual void OnEvent() override;
};
