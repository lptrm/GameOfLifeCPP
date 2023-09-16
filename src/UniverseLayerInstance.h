#pragma once
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "InstanceBufferLayout.h"
#include "Shader.h"
#include "Universe.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "glm.hpp"
#include <functional>
#include <memory>
class UniverseLayerInstance {
public:
  UniverseLayerInstance(float vertexWidth, float vertexHeight,
                        unsigned int width, unsigned int height,
                        float m_GenerationTime,
                        std::function<glm::mat4()> viewProjectionCallback);
  ~UniverseLayerInstance();
  inline float &GetVertexWidth() { return m_VertexWidth; }
  inline float &GetVertexHeight() { return m_VertexHeight; }
  inline float &GetUniverseHeight() { return UniverseHeight; }
  inline unsigned int &GetWidth() { return m_Width; }
  inline unsigned int &GetHeight() { return m_Height; }
  inline glm::vec2 &GetTranslation() { return m_Translation; }
  inline glm::vec2 &GetOffset() { return m_Offset; }
  inline glm::mat4 &GetMVP() { return u_MVP; }
  inline glm::mat4 &GetModel() { return m_MatModel; }
  inline std::shared_ptr<Universe> &GetUniverse() { return m_Universe; }
  inline float &GetGenerationTime() { return m_GenerationTime; }
  inline float &GetLastTimeUniverse() { return m_LastTimeUniverse; }

  bool UniverseIntersection(glm::vec2 &intersectionPoint);
  void ImGuiRender();
  void Unbind();
  void Bind();
  void Draw();

  bool isGarbage = false;

private:
  std::string m_UniverseString;
  static unsigned int instanceCount;
  float m_LastTimeUniverse;
  float m_GenerationTime;
  float m_VertexWidth;
  float m_VertexHeight;
  float UniverseHeight;
  float fillRandomly = 0.0f;
  unsigned int m_Width;
  unsigned int m_Height;
  glm::vec2 m_Offset;
  glm::vec2 m_Translation;
  glm::mat4 u_MVP;
  glm::mat4 m_MatModel;
  std::shared_ptr<Universe> m_Universe;
  std::shared_ptr<Shader> m_Shader;
  std::shared_ptr<VertexArray> m_Va;
  std::shared_ptr<VertexBuffer> m_Vb;
  std::shared_ptr<VertexBufferLayout> m_Layout;
  std::shared_ptr<IndexBuffer> m_Ib;
  std::shared_ptr<InstanceBuffer> m_InstanceBuffer;
  std::shared_ptr<InstanceBufferLayout> m_InstanceLayout;
  std::function<glm::mat4()> m_ViewProjectionCallback;
};
