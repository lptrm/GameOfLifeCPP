#pragma once

#include "fwd.hpp"
#include <glm.hpp>
#include <vector>

class Universe {
public:
  struct CellInstance {
    glm::vec3 color;
    glm::vec3 position;
  };

  Universe(int, int);
  Universe(Universe &&) = default;
  Universe(const Universe &) = default;
  Universe &operator=(Universe &&) = default;
  Universe &operator=(const Universe &) = default;
  ~Universe();
  void FillRandomly(float density);
  void ResetUniverse();

  void update();
  void setAlive(int, int);
  void setDead(int, int);
  void printGrid();
  void printPositionData() const;
  inline int getWidth() const { return m_Width; }
  inline int getHeight() const { return m_Height; }
  inline int getSize() const { return m_Size; }
  inline int getPowerX() const { return m_PowX; }
  inline int getPowerY() const { return m_PowY; }
  inline int *getGameGrid() const { return m_CurrentState; }
  inline int getGameGrid(int index) const { return m_CurrentState[index]; }
  // now passing by reference to update the positions from tha app
  inline std::vector<CellInstance> &getCellInstance() { return m_InstanceData; }

private:
  int m_Width;
  int m_Height;
  int m_PowX;
  int m_PowY;
  int m_Size;
  int *m_CurrentState;
  int *m_OldState;
  std::vector<CellInstance> m_InstanceData;
  int CalculatePower(int);
  bool getOldBitValue(int &index, int &intIndex, int &bitIndex);
  bool getNewBitValue(int &index, int &intIndex, int &bitIndex);
  bool GetBit(int);
  int GetCircularRow(int, int);
  int GetCircularColumn(int, int);
  bool IterateThroughNeighbors(int &index, int &intIndex, bool &bitValue);
};
