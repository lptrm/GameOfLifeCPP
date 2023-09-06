#include "OrthographicCameraController.h"

#include "GLFW/glfw3.h"
#include "Input.h"
#include <iostream>

namespace GLCore::Utils {

OrthographicCameraController::OrthographicCameraController(float aspectRatio,
                                                           bool rotation)
    : m_AspectRatio(aspectRatio),
      m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
               -m_ZoomLevel, m_ZoomLevel),
      m_Rotation(rotation) {}

void OrthographicCameraController::OnUpdate(float ts) {
  if (Input::IsKeyPressed(GLFW_KEY_A)) {
    m_CameraPosition.x -=
        cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    m_CameraPosition.y -=
        sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
  } else if (Input::IsKeyPressed(GLFW_KEY_D)) {
    m_CameraPosition.x +=
        cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    m_CameraPosition.y +=
        sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
  }

  if (Input::IsKeyPressed(GLFW_KEY_W)) {
    m_CameraPosition.x +=
        -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    m_CameraPosition.y +=
        cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
  } else if (Input::IsKeyPressed(GLFW_KEY_S)) {
    m_CameraPosition.x -=
        -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    m_CameraPosition.y -=
        cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
  }

  if (m_Rotation) {
    if (Input::IsKeyPressed(GLFW_KEY_Q))
      m_CameraRotation += m_CameraRotationSpeed * ts;
    if (Input::IsKeyPressed(GLFW_KEY_E))
      m_CameraRotation -= m_CameraRotationSpeed * ts;

    if (m_CameraRotation > 180.0f)
      m_CameraRotation -= 360.0f;
    else if (m_CameraRotation <= -180.0f)
      m_CameraRotation += 360.0f;

    m_Camera.SetRotation(m_CameraRotation);
  }

  m_Camera.SetPosition(m_CameraPosition);

  m_CameraTranslationSpeed = m_ZoomLevel;
}

void OrthographicCameraController::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  // Dispatch MouseScrolledEvent to OnMouseScrolled member function
  dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent &event) {
    return this->OnMouseScrolled(event);
  });

  // Dispatch WindowResizeEvent to OnWindowResized member function
  dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent &event) {
    return this->OnWindowResized(event);
  });
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e) {
  m_ZoomLevel -= e.GetYOffset() * 0.25f;
  m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
  m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                         m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                         m_ZoomLevel);
  return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e) {
  m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
  m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                         m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                         m_ZoomLevel);
  return false;
}

} // namespace GLCore::Utils
