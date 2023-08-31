#pragma once

#include "IndexBuffer.h"
#include "Renderer.h"
#include "glad/glad.h"

#pragma once

class Shader;
class VertexArray;
class InstanceBuffer;

// Function to clear OpenGL errors
inline void GLClrearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

// Function to check OpenGL errors
bool GLLogCall(const char *function, const char *file, int line);

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
  GLClrearError();                                                             \
  x;                                                                           \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))
bool GLLogCall(const char *function, const char *file, int line);
class Renderer {
public:
  void Clear() const;
  void Draw(const VertexArray &va, const IndexBuffer &ib,
            const InstanceBuffer &instncb, const Shader &shader) const;
};
