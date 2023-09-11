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
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "imgui.h"
#include "utils/Camera/OrthographicCameraController.h"
#include <memory>

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

private:
  std::shared_ptr<GLCore::Utils::OrthographicCameraController>
      m_CameraController;
  glm::mat4 u_MVP;
  glm::mat4 m_MatModel;
  std::shared_ptr<Shader> m_Shader;
  std::shared_ptr<VertexArray> m_Va;
  std::shared_ptr<VertexBuffer> m_Vb;
  std::shared_ptr<VertexBufferLayout> m_Layout;
  std::shared_ptr<IndexBuffer> m_Ib;
  std::shared_ptr<InstanceBuffer> m_InstanceBuffer;
  std::shared_ptr<InstanceBufferLayout> m_InstanceLayout;
  std::shared_ptr<Universe> m_Universe;
  double m_LastTimeUniverse;
  double m_GenerationTime;
  double m_LastTimeFrame;
  unsigned int m_Width;
  unsigned int m_Height;
  float m_ScreenWidth;
  float m_ScreenHeight;
  float m_VertexWidth;
  float m_VertexHeight;
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  void Unbind();
  void Bind();
};
