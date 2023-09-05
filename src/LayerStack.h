#pragma once
#include "Event.h"
#include <string>
#include <vector>
class Layer {
public:
  inline Layer(const std::string &name) : m_DebugName(name){};
  virtual ~Layer() = default;

  virtual void OnAttach(){};
  virtual void OnDetach(){};
  virtual void OnUpdate(const double timeStamp){};
  virtual void OnEvent(GLCore::Event &event){};

  inline const std::string &GetName() const { return m_DebugName; };

protected:
  std::string m_DebugName;
};
class LayerStack {
public:
  void PushLayer(Layer *layer);
  void PopLayer(Layer *layer);
  void UpdateLayers(const double timeStamp);
  void RenderLayers();
  void HandleEvents();
  std::vector<Layer *>::iterator begin() { return layers.begin(); }
  std::vector<Layer *>::iterator end() { return layers.end(); }

private:
  std::vector<Layer *> layers;
};
