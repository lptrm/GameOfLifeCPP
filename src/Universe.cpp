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
  m_CurrentState = new int[size]();
  m_OldState = new int[size]();
  m_InstanceData = std::vector<CellInstance>(m_Size);
  for (int i = 0; i < m_Size; i++) {
    m_InstanceData[i].color =
        i % 2 == 0 ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(0.0f, 0.0f, 1.0f);
  }
}
Universe::~Universe() {
  delete[] m_CurrentState;
  delete[] m_OldState;
}
void Universe::update() {
  std::swap(m_CurrentState, m_OldState); // Swap the current and old state
  m_CurrentState = new int[m_Size]();
  for (int i = 0; i < m_Size; i++) {
    int intIndex, bitOffset;
    bool oldState = getOldBitValue(i, intIndex, bitOffset);
    bool newState =
        IterateThroughNeighbors(i, intIndex, oldState); // Determine new state
    if (newState) {
      m_CurrentState[intIndex] |=
          (1 << bitOffset); // Set the corresponding bit to 1
      m_InstanceData[i].color = glm::vec3(1.0f, 0.0f, 1.0f);
    } else {
      m_InstanceData[i].color = glm::vec3(0.0f, 1.0f, 1.0f);
    }
  }
}
// Function to print the position data of CellInstance objects
void Universe::printPositionData() const {
  std::cout << "Position Data of the Universe:" << std::endl;

  for (const Universe::CellInstance &instance : m_InstanceData) {
    std::cout << "Position=(" << instance.position.x << ", "
              << instance.position.y << ", " << instance.position.z << ")"
              << std::endl;
  }
}
void Universe::setAlive(int column, int row) {
  int index = row * column + column;
  int intIndex = index >> 5;
  int bitOffset = index & 31;
  m_CurrentState[intIndex] |= (1 << bitOffset);
}
bool Universe::getOldBitValue(int &index, int &intIndex, int &bitOffset) {
  intIndex = index >> 5;
  bitOffset = index & 31;
  return (m_OldState[intIndex] >> bitOffset) & 1;
}
bool Universe::getNewBitValue(int &index, int &intIndex, int &bitOffset) {
  intIndex = index >> 5;
  bitOffset = index & 31;
  return (m_CurrentState[intIndex] >> bitOffset) & 1;
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

      int neighborBit = (m_OldState[neighborIntIndex] >> neighborBitOffset) & 1;
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
    int bitValue = (this->m_CurrentState[intIndex] >> bitIndex) & 1;
    std::cout << bitValue << "";
    if ((i + 1) % this->m_Width == 0) {
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}
