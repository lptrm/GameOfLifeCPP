#include "Universe.h"
#include <iostream>
Universe::Universe(int width, int height, GLint ShaderProgram)
    : m_Width(width), m_Height(height), m_ShaderProgram(ShaderProgram) {
  if ((m_Width & (m_Width - 1)) != 0 || (m_Height & (m_Height - 1)) != 0) {
    return; // TODO: Throw exception
  }
  m_PowX = CalculatePower(m_Width);
  m_PowY = CalculatePower(m_Height);
  int size = 1 << (m_PowX + m_PowY - 5);
  m_Size = width << m_PowY;
  m_GameGrid = new int[size]();

  glGenTextures(1, &gameGridTexture);
  glBindTexture(GL_TEXTURE_2D, gameGridTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Set the initial game grid data as the texture's content
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0, GL_RED,
               GL_UNSIGNED_BYTE, nullptr);
}
Universe::~Universe() { delete[] m_GameGrid; }
void Universe::update() {
  int *newGameGrid = new int[m_Size](); // Create a new array for updated state
  std::vector<unsigned char> gameGridData(m_Width * m_Height);
  for (int i = 0; i < m_Size; i++) {
    int intIndex, bitOffset;
    bool oldState = GetBitValue(i, intIndex, bitOffset);
    bool newState =
        IterateThroughNeighbors(i, intIndex, oldState); // Determine new state
    if (newState) {
      newGameGrid[intIndex] |=
          (1 << bitOffset); // Set the corresponding bit to 1
    }
    gameGridData[i] = newState ? 255 : 0;
  }

  // Copy the new array back to the original grid
  delete[] m_GameGrid; // Free the memory of the old grid
  m_GameGrid = newGameGrid;
  updateTexture(gameGridData); // Update the game grid texture
}
void ::Universe::updateTexture(std::vector<unsigned char> &gameGridData) {
  glBindTexture(GL_TEXTURE_2D, gameGridTexture);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RED,
                  GL_UNSIGNED_BYTE, &gameGridData);
  glBindTexture(GL_TEXTURE_2D, 0);
  glUniform1i(glGetUniformLocation(m_ShaderProgram, "gameGrid"),
              0); // Use texture unit 0
  // Unbind shader program and texture
  glUseProgram(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
void ::Universe::bindTexture() {
  glActiveTexture(GL_TEXTURE0); // Choose a texture unit (e.g., unit 0)
  glBindTexture(GL_TEXTURE_2D, gameGridTexture);
}
bool Universe::GetBitValue(int &index, int &intIndex, int &bitOffset) {
  intIndex = index >> 5;
  bitOffset = index & 31;
  return (m_GameGrid[intIndex] >> bitOffset) & 1;
}
bool Universe::IterateThroughNeighbors(int &index, int &intIndex,
                                       bool &oldState) {
  int neighborCount = 0;
  for (int dr = -1; dr <= 1 && neighborCount < 4; ++dr) {
    for (int dc = -1; dc <= 1 && neighborCount < 4; ++dc) {
      if (dr == 0 && dc == 0)
        continue; // Skip the current cell
      int newRow = (((index >> m_PowX) + dr) & (m_Height - 1));
      int newCol = ((index & (m_Width - 1)) + dc) & (m_Width - 1);
      int neighborIndex = newRow * m_Width + newCol;
      int neighborIntIndex = neighborIndex >> 5;
      int neighborBitOffset = neighborIndex & 31;

      int neighborBit = (m_GameGrid[neighborIntIndex] >> neighborBitOffset) & 1;
      if (neighborBit != 0) {
        neighborCount++;
      }
    }
  }
  return (neighborCount == 3 || neighborCount == 2 && oldState);
  // maybe use later for fine tuning
  // neighborBits |= (neighborBit << (dr + 1) * 3 + dc + 1);
}
int Universe::CalculatePower(int value) {
  int pow = 0;
  while (value > 1) {
    value >>= 1;
    pow++;
  }
  return pow;
}
void Universe::printGrid() {
  for (int i = 0; i < this->m_Size; i++) {
    int intIndex = i >> 5;
    int bitIndex = i & 31;
    int bitValue = (this->m_GameGrid[intIndex] >> bitIndex) & 1;
    std::cout << bitValue << "";
    if ((i + 1) % this->m_Width == 0) {
      std::cout << std::endl;
    }
  }
}
