#include "glad/glad.h"
#include <iostream>

#pragma once

// Function to clear OpenGL errors
inline void GLCLrearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

// Function to check OpenGL errors
inline bool GLLogCall(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    std::cerr << "[OpenGL Error] (" << error << "): " << function << " " << file
              << ":" << line << std::endl;
    return false;
  }
  return true;
}

// Macro for assertions
#ifdef _MSC_VER
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    __debugbreak();
#else
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    __builtin_trap();
#endif
// Macro for OpenGL error checking
#define GLCALL(x)                                                              \
  GLCLrearError();                                                             \
  x;                                                                           \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))
