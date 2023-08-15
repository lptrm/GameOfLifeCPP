#include "Universe.h"
#include <iostream>
Universe::Universe(int width, int height) : m_Width(width), m_Height(height) {
  if ((m_Width & (m_Width - 1)) != 0 || (m_Height & (m_Height - 1)) != 0) {
    return; // TODO: Throw exception
  }
  m_PowX = CalculatePower(m_Width);
  m_PowY = CalculatePower(m_Height);
  int size = 1 << (m_PowX + m_PowY - 5);
  m_Size = width << m_PowY;
  m_GameGrid = new int[size]();
}
Universe::~Universe() { delete[] m_GameGrid; }
void Universe::update() {
  int *newGameGrid = new int[m_Size](); // Create a new array for updated state

  for (int i = 0; i < m_Size; i++) {
    int intIndex, bitOffset;
    bool oldState = GetBitValue(i, intIndex, bitOffset);
    bool newState =
        IterateThroughNeighbors(i, intIndex, oldState); // Determine new state
    if (newState) {
      newGameGrid[intIndex] |=
          (1 << bitOffset); // Set the corresponding bit to 1
    }
  }

  // Copy the new array back to the original grid
  delete[] m_GameGrid; // Free the memory of the old grid
  m_GameGrid = newGameGrid;
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
