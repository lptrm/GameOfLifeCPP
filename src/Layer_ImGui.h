#pragma once

#include "Event.h"
#include "LayerStack.h"
#include "imgui.h"

class ImGuiLayer : public Layer {

public:
  ImGuiLayer() : Layer("ImGuiLayer"){};
  ~ImGuiLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void Begin();
  virtual void End();
};
