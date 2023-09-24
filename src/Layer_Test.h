#pragma once

#include "Event.h"
#include "IndexBuffer.h"
#include "LayerStack.h"
#include "Shader.h"
#include "VertexArray.h"
#include "imgui.h"
#include <memory>

class TestLayer : public Layer {
  std::shared_ptr<VertexArray> m_Va;
  std::shared_ptr<VertexBuffer> m_Vb;
  std::shared_ptr<VertexBufferLayout> m_Layout;
  std::shared_ptr<Shader> m_Shader;
  std::shared_ptr<VertexArray> a_Va;
  std::shared_ptr<VertexBuffer> a_Vb;
  std::shared_ptr<VertexBufferLayout> a_Layout;
  std::shared_ptr<Shader> a_Shader;
  glm::mat4 m_Proj, m_View, m_Model, u_MVP, a_MVP;
  float m_PerspectiveFOV;
  float m_PerspectiveNear;
  float m_PerspectiveFar;
  float m_AspectRatio;
  float m_OrthographicSize;
  float m_OrthographicNear;
  float m_OrthographicFar;
  float m_OrthographicLeft;
  float m_OrthographicRight;
  float m_OrthographicBottom;
  float m_OrthographicTop;
  float m_CameraYaw;
  float m_CameraPitch;
  bool m_CameraType = true;
  glm::vec3 m_Eye;
  glm::vec3 m_Center;
  glm::vec3 m_Up;

  void Bind();
  void Unbind();

public:
  TestLayer() : Layer("TestLayer"){};
  ~TestLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate(const float timeStamp) override;
  virtual void OnEvent(GLCore::Event &e) override;
  virtual void OnImGuiRender() override;
};
