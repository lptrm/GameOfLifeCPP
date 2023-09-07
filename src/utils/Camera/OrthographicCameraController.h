#pragma once

#include "OrthographicCamera.h"

#include "ApplicationEvent.h"
#include "MouseEvent.h"

namespace GLCore::Utils {

class OrthographicCameraController {
public:
  OrthographicCameraController(float aspectRatio, bool rotation = false);

  void OnUpdate(float ts);
  void OnEvent(Event &e);

  OrthographicCamera &GetCamera() { return m_Camera; }
  const OrthographicCamera &GetCamera() const { return m_Camera; }

  float GetZoomLevel() const { return m_ZoomLevel; }
  void SetZoomLevel(float level) { m_ZoomLevel = level; }

private:
  bool OnMouseScrolled(MouseScrolledEvent &e);
  bool OnWindowResized(WindowResizeEvent &e);

private:
  float m_AspectRatio;
  float m_ZoomLevel = 1.0f;
  OrthographicCamera m_Camera;

  bool m_Rotation;

  glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
  float m_CameraRotation = 0.0f; // In degrees, in the anti-clockwise direction
  float m_CameraTranslationSpeed = 0.1f, m_CameraRotationSpeed = 45.0f;
};

} // namespace GLCore::Utils
