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

class UniverseLayer : public Layer {
  // Declare pointers to objects
  glm::mat4 *m_Mvp;
  Shader *m_Shader;
  VertexArray *m_Va;
  VertexBuffer *m_Vb;
  VertexBufferLayout *m_Layout;
  IndexBuffer *m_Ib;
  InstanceBuffer *m_InstanceBuffer;
  InstanceBufferLayout *m_InstanceLayout;
  Universe *m_Universe;
  double m_LastTime;
  double m_GenerationTime;
  GLCore::Utils::OrthographicCameraController *m_CameraController;

public:
  UniverseLayer() : Layer("UniverseLayer"){};
  ~UniverseLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const double timeStamp) override;
  virtual void OnEvent(GLCore::Event &e) override;
};
