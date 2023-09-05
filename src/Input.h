#pragma once
#include <utility>
class Input {
  static Input *s_Instance;
  Input() = default;

public:
  static bool IsKeyPressed(int keycode);

  static bool IsMouseButtonPressed(int button);
  static std::pair<float, float> GetMousePosition();
  static float GetMouseX();
  static float GetMouseY();
};
