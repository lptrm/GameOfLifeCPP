#pragma once

#include "Event.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "InstanceBufferLayout.h"
#include "LayerStack.h"
#include "Renderer.h"
#include "Shader.h"
#include "Universe.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "utils/Camera/OrthographicCameraController.h"
#include <memory>

class UniverseLayer : public Layer {
public:
  UniverseLayer();
  ~UniverseLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const double timeStamp) override;
  virtual void OnEvent(GLCore::Event &e) override;

  void TestFunction();

private:
  GLCore::Utils::OrthographicCameraController *m_CameraController;
  glm::mat4 *m_Mvp;
  Shader *m_Shader;
  VertexArray *m_Va;
  VertexBuffer *m_Vb;
  VertexBufferLayout *m_Layout;
  IndexBuffer *m_Ib;
  InstanceBuffer *m_InstanceBuffer;
  InstanceBufferLayout *m_InstanceLayout;
  Universe *m_Universe;
  double m_LastTimeUniverse;
  double m_GenerationTime;
  double m_LastTimeFrame;
  unsigned int m_Width;
  unsigned int m_Height;
};
