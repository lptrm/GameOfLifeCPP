#pragma once

#include "fwd.hpp"
#include <glm.hpp>
#include <vector>

class Universe {
public:
  struct CellInstance {
    glm::vec3 position;
    glm::vec3 color;
  };

  Universe(int, int);
  Universe(Universe &&) = default;
  Universe(const Universe &) = default;
  Universe &operator=(Universe &&) = default;
  Universe &operator=(const Universe &) = default;
  ~Universe();
  void update();
  void setAlive(int, int);
  void setDead(int, int);
  void printGrid();
  inline int getWidth() const { return m_Width; }
  inline int getHeight() const { return m_Height; }
  inline int getSize() const { return m_Size; }
  inline int getPowerX() const { return m_PowX; }
  inline int getPowerY() const { return m_PowY; }
  inline int *getGameGrid() const { return m_GameGrid; }
  inline int getGameGrid(int index) const { return m_GameGrid[index]; }
  inline std::vector<unsigned char> getGameGridData() const {
    return m_GameGridData;
  }
  inline std::vector<CellInstance> getCellInstance() const {
    return m_InstanceData;
  }

private:
  int m_Width;
  int m_Height;
  int m_PowX;
  int m_PowY;
  int m_Size;
  int *m_GameGrid;
  std::vector<unsigned char> m_GameGridData;
  std::vector<CellInstance> m_InstanceData;
  int CalculatePower(int);
  bool GetBitValue(int &index, int &intIndex, int &bitIndex);
  bool GetBit(int);
  int GetCircularRow(int, int);
  int GetCircularColumn(int, int);
  bool IterateThroughNeighbors(int &index, int &intIndex, bool &bitValue);
};
