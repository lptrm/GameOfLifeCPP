#include "LayerStack.h"
#include <algorithm>

void LayerStack::PushLayer(Layer *layer) {
  layers.push_back(layer);
  layer->OnAttach();
}

void LayerStack::PopLayer(Layer *layer) {
  auto it = std::find(layers.begin(), layers.end(), layer);
  if (it != layers.end()) {
    layers.erase(it);
    layer->OnDetach();
  }
}

void LayerStack::UpdateLayers(const double timeStamp) {
  for (auto &layer : layers) {
    layer->OnUpdate(timeStamp);
  }
}
