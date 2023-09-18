#pragma once

#include "Event.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "InstanceBufferLayout.h"
#include "LayerStack.h"
#include "Renderer.h"
#include "Shader.h"
#include "Universe.h"
#include "UniverseLayerInstance.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ext/matrix_transform.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "imgui.h"
#include "utils/Camera/OrthographicCameraController.h"
#include <memory>
#include <vector>

class UniverseLayer : public Layer {
public:
  UniverseLayer(float screenWidth, float screenHeight, float vertexWidth,
                float vertexHeight, unsigned int width, unsigned int height);
  ~UniverseLayer();
  void FillRandomly(float density);
  void ResetUniverse();
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const float timeStamp) override;
  virtual void OnImGuiRender() override;
  virtual void OnEvent(GLCore::Event &e) override;

  void TestFunction();
  bool UniverseIntersection(glm::vec2 &intersectionPoint);
  inline glm::mat4 GetViewProjectionMatrix() {
    return m_CameraController->GetCamera().GetViewProjectionMatrix();
  };

private:
  std::shared_ptr<GLCore::Utils::OrthographicCameraController>
      m_CameraController;

  std::vector<UniverseLayerInstance> m_UniverseInstances;

  float m_LastTimeFrame;

  float m_ScreenWidth;
  float m_ScreenHeight;
  static float totalTimeUniverse;
  static int frameCountUniverse;

  static float totalTimeDraw;
  static int frameCountDraw;
bool isPaused = false;
  bool errorPopup = false;
  const char *errorMessage;
};
