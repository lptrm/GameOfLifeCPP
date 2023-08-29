#pragma once
#include <string>
#include <vector>
class Layer {
public:
  inline Layer(const std::string &name = "Layer") : m_DebugName(name){};
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnImGuiRender() {}
  virtual void OnEvent() {}

  inline const std::string &GetName() const { return m_DebugName; }

protected:
  std::string m_DebugName;
};
class LayerStack {
public:
  void PushLayer(Layer *layer);
  void PopLayer(Layer *layer);
  void UpdateLayers();
  void RenderLayers();
  void HandleEvents();

private:
  std::vector<Layer *> layers;
};
