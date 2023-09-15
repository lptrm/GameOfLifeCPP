#include "UniverseLayerInstance.h"
#include "Renderer2D.h"
#include "ext/matrix_transform.hpp"
#include "fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include <iostream>
UniverseLayerInstance::UniverseLayerInstance(
    float vertexWidth, float vertexHeight, unsigned int width,
    unsigned int height, float generationTime,
    std::function<glm::mat4()> viewProjectionCallback)
    : m_VertexWidth(vertexWidth), m_VertexHeight(vertexHeight), m_Width(width),
      m_Height(height), m_GenerationTime(generationTime),
      m_ViewProjectionCallback(viewProjectionCallback) {
  m_LastTimeUniverse = 0.0f;

  m_Offset =
      glm::vec2(vertexWidth * width * -0.5f, vertexHeight * height * -0.5f);
  m_Translation = glm::vec2(0.0f, 0.0f);
  glm::vec2 translation = m_Offset + m_Translation;
  m_MatModel = glm::translate(glm::mat4(1.0f), glm::vec3(translation, 0.0f));
  m_Shader = std::make_shared<Shader>(
      "/home/jano/dev/nvim/GameOfLifeCPP/assets/gol.shader");

  float vertices[] = {0.0f, 0.0f, 0.0f,           m_VertexWidth,
                      0.0f, 0.0f, m_VertexWidth,  m_VertexHeight,
                      0.0f, 0.0f, m_VertexHeight, 0.0f};
  m_Va = std::make_shared<VertexArray>();
  m_Va->Bind();

  m_Vb = std::make_shared<VertexBuffer>(vertices, 4 * 3 * sizeof(float));

  m_Layout = std::make_shared<VertexBufferLayout>();
  m_Layout->Push<float>(3);

  m_Va->AddBuffer(*m_Vb, *m_Layout);

  GLuint indices[] = {0, 1, 2, 2, 3, 0};
  m_Ib = std::make_shared<IndexBuffer>(indices, 6);

  m_Universe = std::make_shared<Universe>(m_Width, m_Height);
  for (int i = 0; i < m_Height; i++) {
    for (int j = 0; j < m_Width; j++) {
      m_Universe->getCellInstance()[i * m_Width + j].position =
          glm::vec3(j * m_VertexWidth, i * m_VertexHeight, 0.0f);
    }
  }
  m_Universe->FillRandomly(0.5f);

  m_InstanceBuffer = std::make_shared<InstanceBuffer>(
      m_Universe->getCellInstance().data(),
      sizeof(Universe::CellInstance) * m_Universe->getCellInstance().size());
  m_InstanceLayout = std::make_shared<InstanceBufferLayout>();
  m_InstanceLayout->Push<float>(4);
  m_InstanceLayout->Push<float>(3);
  m_InstanceBuffer->addAttributePointer(*m_InstanceLayout);
  std::cout << "UniverseLayerInstance::UniverseLayerInstance()" << std::endl;
  u_MVP = m_ViewProjectionCallback() * m_MatModel;
  std::cout << "UniverseLayerInstance::UniverseLayerInstance()" << std::endl;
  m_Shader->SetUniformMat4f("u_MVP", u_MVP);
  m_LastTimeUniverse = 0.0f;
  m_GenerationTime = 5.0;
  Unbind();
};
void UniverseLayerInstance::Bind() {
  m_Va->Bind();
  m_Shader->Bind();
}
void UniverseLayerInstance::Unbind() {
  m_Va->Unbind();
  m_Shader->Unbind();
}
void UniverseLayerInstance::Draw() {
  glm::vec2 translation = m_Offset + m_Translation;
  m_MatModel = glm::translate(glm::mat4(1.0f), glm::vec3(translation, 0.0f));
  u_MVP = m_ViewProjectionCallback() * m_MatModel;
  m_InstanceBuffer->UpdateInstanceData(m_Universe->getCellInstance().data(),
                                       m_Universe->getCellInstance().size() *
                                           sizeof(Universe::CellInstance));
  Renderer2D::DrawInstanced(m_Va, m_Shader, m_InstanceBuffer, u_MVP,
                            m_Universe->getCellInstance().size());
}
bool UniverseLayerInstance::UniverseIntersection(glm::vec2 &screenCoords) {

  glm::vec4 worldCoords = glm::inverse(m_ViewProjectionCallback()) *
                          glm::vec4(screenCoords, 0.0f, 1.0f);
  worldCoords /= worldCoords.w;

  if (worldCoords.x < m_VertexWidth * m_Width * -0.5f ||
      worldCoords.x > m_VertexWidth * m_Width * 0.5f ||
      worldCoords.y < m_VertexHeight * m_Height * -0.5f ||
      worldCoords.y > m_VertexHeight * m_Height * 0.5f) {
    std::cout << "Out of bounds" << std::endl;
    return false;
  }
  glm::vec4 intersectionPoint =
      glm::inverse(

          m_MatModel) *
      glm::vec4(worldCoords.x, worldCoords.y, 0.0f, 1.0f);
  int row = (int)(intersectionPoint.y / m_VertexHeight);
  int col = (int)(intersectionPoint.x / m_VertexWidth);
  m_Universe->setAlive(col, row);
  return true;
}
void UniverseLayerInstance::ImGuiRender() {

  ImGui::Text("This is some useful text."); // Display some text (you can use
                                            // a format strings too)
  ImGui::SliderFloat("time for generation (s)", &m_GenerationTime, 0.0f,
                     10.0f); // Edit 1 float using a slider from 0.0f to 1.0f
  ImGui::SliderFloat("density(alive) after reset (s)", &fillRandomly, 0.0f,
                     1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
  if (ImGui::SliderFloat2("translation of the universe",
                          glm::value_ptr(m_Translation), -1000.0f, 1000.0f)) {

  }; // Edit 1 float using a slider from 0.0f to 1.0f
     // &m_UniverseInstances[0].m_MatModel)

  if (ImGui::Button("Reset Universe")) {
    m_Universe->ResetUniverse();
    m_Universe->FillRandomly(fillRandomly);
  } // Buttons return true when clicked
  if (ImGui::ColorEdit4("alive color",
                        glm::value_ptr(m_Universe->getColorAlive())) ||
      ImGui::ColorEdit4("dead color",
                        glm::value_ptr(m_Universe->getColorDead()))) {
    m_Universe->UpdateColors();
  };
}
