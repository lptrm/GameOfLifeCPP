#pragma once

#include "LayerStack.h"

class ImGuiLayer : public Layer {
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const double timeStamp) override;
  virtual void OnEvent() override;
};
