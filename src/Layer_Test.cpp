#include "Layer_Test.h"
#include "OpenGLRendererAPI.h"
#include "Renderer2D.h"
#include "VertexBufferLayout.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include "utils/Renderer/RenderCommand.h"
#include <iostream>
#include <memory>

void TestLayer::OnAttach() { //  Implementation for OnAttach, if needed
  m_Proj = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
  m_View =
      glm::lookAt(glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
                  glm::vec3(0, 0, 0), // and looks at the origin
                  glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look
                                      // upside-down)
      );
  m_Model = glm::mat4(1.0f);
  u_MVP = m_Proj * m_View * m_Model;
  float positions[] = {
      -1.0f, -1.0f, -1.0f,                      // triangle 1 : begin
      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  // triangle 1 : end
      1.0f,  1.0f,  -1.0f,                      // triangle 2 : begin
      -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, // triangle 2 : end
      1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,
      1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
      -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
      -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f};

  float colors[] = {
      0.583f, 0.771f, 0.014f, 0.609f, 0.115f, 0.436f, 0.327f, 0.483f, 0.844f,
      0.822f, 0.569f, 0.201f, 0.435f, 0.602f, 0.223f, 0.310f, 0.747f, 0.185f,
      0.597f, 0.770f, 0.761f, 0.559f, 0.436f, 0.730f, 0.359f, 0.583f, 0.152f,
      0.483f, 0.596f, 0.789f, 0.559f, 0.861f, 0.639f, 0.195f, 0.548f, 0.859f,
      0.014f, 0.184f, 0.576f, 0.771f, 0.328f, 0.970f, 0.406f, 0.615f, 0.116f,
      0.676f, 0.977f, 0.133f, 0.971f, 0.572f, 0.833f, 0.140f, 0.616f, 0.489f,
      0.997f, 0.513f, 0.064f, 0.945f, 0.719f, 0.592f, 0.543f, 0.021f, 0.978f,
      0.279f, 0.317f, 0.505f, 0.167f, 0.620f, 0.077f, 0.347f, 0.857f, 0.137f,
      0.055f, 0.953f, 0.042f, 0.714f, 0.505f, 0.345f, 0.783f, 0.290f, 0.734f,
      0.722f, 0.645f, 0.174f, 0.302f, 0.455f, 0.848f, 0.225f, 0.587f, 0.040f,
      0.517f, 0.713f, 0.338f, 0.053f, 0.959f, 0.120f, 0.393f, 0.621f, 0.362f,
      0.673f, 0.211f, 0.457f, 0.820f, 0.883f, 0.371f, 0.982f, 0.099f, 0.879f};
  float data[12 * 3 * 3 * 2];
  for (int i = 0; i < 12 * 3 * 3 * 2; i++) {
    int col = i % 6;
    int row = i / 6;
    if (col < 3) {
      data[i] = positions[i - 3 * row];
    } else {
      data[i] = colors[i - 3 * row - 3];
    }
  }
  for (int i = 0; i < 12 * 3 * 3 * 2; i++) {
    std::cout << data[i] << " " << std::endl;
  }
  m_Va = std::make_shared<VertexArray>();
  m_Vb = std::make_shared<VertexBuffer>(data, 12 * 3 * 3 * 2 * sizeof(float));
  m_Layout = std::make_shared<VertexBufferLayout>();
  m_Layout->Push<float>(3);
  m_Layout->Push<float>(3);
  m_Va->AddBuffer(*m_Vb, *m_Layout);

  m_Shader = std::make_shared<Shader>(
      "/home/jano/dev/nvim/GameOfLifeCPP/assets/cube.shader");
  m_Shader->SetUniformMat4f("u_MVP", u_MVP);
  Unbind();
}

void TestLayer::OnDetach() {}

void TestLayer::OnUpdate(const float timeStamp) {

  Renderer2D::DrawTest(m_Va, m_Shader, u_MVP, 12 * 3);
}

void TestLayer::OnEvent(GLCore::Event &e) {
  // Implementation for OnEvent, if needed
}
void TestLayer::Bind() { m_Shader->Bind(); }
void TestLayer::Unbind() {
  m_Va->Unbind();
  m_Shader->Unbind();
}
