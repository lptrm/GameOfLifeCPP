#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string &path)
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0),
      m_Height(0), m_BPP(0) {
  // Flip the image vertically
  // OpenGL expects the 0.0 coordinate on the y-axis to be on the bottom side of
  // the image
  stbi_set_flip_vertically_on_load(1);
  // Load the image
  m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
  // Generate a texture
  GLCALL(glGenTextures(1, &m_RendererID));
  // Bind the texture
  GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
  // Scales the image linearly if its smaller than the texture
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  // Scales the image linearly if its bigger than the texture
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  // Sets the texture wrapping to clamp to edge on x-axis (S)
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  // Sets the texture wrapping to clamp to edge on y-axis (T)
  GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  // Set the texture data, 0 because of non miltilayered textures for now
  // RGBA8 because we want 4 channels with 8 bits per channel
  GLCALL(glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
      GL_UNSIGNED_BYTE,
      m_LocalBuffer)); // may be provided a nullptr for allocating GPU-memory
  // Unbind the texture
  GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
  // Free the image
  if (m_LocalBuffer)
    stbi_image_free(m_LocalBuffer);
}
Texture::~Texture() { GLCALL(glDeleteTextures(1, &m_RendererID)); }
void Texture::Bind(unsigned int slot /* = 0 */) const {
  GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
  GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
void Texture::Unbind() const { GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); }
