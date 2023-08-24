#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <wchar.h>

Shader::Shader(const std::string &filepath)
    : m_FilePath(filepath), m_RendererID(0) {
  ShaderProgramSource source = ParseShader(filepath);

  std::cout << "VERTEX" << std::endl;
  std::cout << source.VertexSource << std::endl;

  m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

  glUseProgram(m_RendererID);
}

Shader::~Shader() { glDeleteProgram(m_RendererID); }
void Shader::Bind() const { glUseProgram(m_RendererID); }
void Shader::Unbind() const { glUseProgram(0); }

GLint Shader::GetUniformLocation(const std::string &name) const {
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache[name];
  GLint location = glGetUniformLocation(m_RendererID, name.c_str());
  if (location == -1)
    std::cout << "Warning: uniform '" << name << "' doesn't exist!"
              << std::endl;
  m_UniformLocationCache[name] = location;
  return location;
}
void Shader::SetUniformSampler2d(const std::string &name, GLuint slot) {
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, &slot);
}
void Shader::SetUniform1i(const std::string &name, int value) {
  glUniform1i(GetUniformLocation(name), value);
}
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3) {
  glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
void Shader::SetUniform3f(const std::string &name, float v0, float v1,
                          float v2) {
  glUniform3f(GetUniformLocation(name), v0, v1, v2);
}
void Shader::SetUniform2f(const std::string &name, float v0, float v1) {
  glUniform2f(GetUniformLocation(name), v0, v1);
}
void Shader::SetUniform1f(const std::string &name, float value) {
  glUniform1f(GetUniformLocation(name), value);
}
void Shader::SetUniformMat3f(const std::string &name, const glm::mat3 &matrix) {
  glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
  glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

struct ShaderProgramSource Shader::ParseShader(const std::string &filepath) {
  // open file
  std::ifstream stream(
      filepath); // Überprüfe, ob die Datei geöffnet werden konnte
  // enum to keep track of shader type
  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
  // string to hold line of code
  std::string line;
  // stringstream to hold shader source code
  std::stringstream ss[2];
  // shader type
  ShaderType type = ShaderType::NONE;

  // while there are lines to read
  while (getline(stream, line)) {
    // if line contains #shader
    if (line.find("#shader") != std::string::npos) {
      // if line contains vertex
      if (line.find("vertex") != std::string::npos) {
        type = ShaderType::VERTEX;
      }
      // if line contains fragment
      else if (line.find("fragment") != std::string::npos) {
        type = ShaderType::FRAGMENT;
      }
    } else {
      // add line to stringstream based on shader type
      ss[(int)type] << line << '\n';
    }
  }
  return {ss[0].str(), ss[1].str()};
}
unsigned int Shader::CompileShader(unsigned int type,
                                   const std::string &source) {
  // Debug print the shader source code
  std::cout << "Shader source code:" << std::endl;
  std::cout << source << std::endl;
  // create shader
  unsigned int id = glCreateShader(type);
  // convert string to char*
  const char *src = source.c_str();
  // set shader source code
  glShaderSource(id, 1, &src, 0);
  // compile shader
  glCompileShader(id);
  // variable to hold compile status
  GLint result;
  // get compile status
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    // get length of error message
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    // create char* to hold error message
    char *message = (char *)alloca(length * sizeof(char));
    // get error message
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile "
              << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!"
              << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}
unsigned int Shader::CreateShader(const std::string &vertexShader,
                                  const std::string &fragmentShader) {
  // create program
  unsigned int program = glCreateProgram();
  // create vertex shader
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  // create fragment shader
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
  // attach shaders to program
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  // link program
  glLinkProgram(program);
  GLint program_linked;

  glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
  std::cout << "Program link status: " << program_linked << std::endl;
  if (program_linked != GL_TRUE) {
    GLsizei log_length = 0;
    GLchar message[1024];
    glGetProgramInfoLog(program, 1024, &log_length, message);
    std::cout << "Failed to link program" << std::endl;
    std::cout << message << std::endl;
  }
  // validate program
  glValidateProgram(program);
  // delete shaders
  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}
