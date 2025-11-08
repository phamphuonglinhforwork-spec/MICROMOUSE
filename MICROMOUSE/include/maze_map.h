#pragma once
#include <vector>
#include <cstdint>

struct Cell {
    uint8_t walls = 0; // bitmask N=1,E=2,S=4,W=8
    int cost = 0;
};

class MazeMap {
public:
    MazeMap(int n = 16);
    int size() const;
    void resetCosts(int largeValue = 99999);
    bool inBounds(int x,int y) const;
    Cell& at(int x,int y);
    const Cell& at(int x,int y) const;
    void setWall(int x,int y, uint8_t wallBits);
    bool wallBetween(int x,int y,int nx,int ny) const;
    bool isCenter(int x,int y) const;
private:
    int N;
    std::vector<std::vector<Cell>> grid;
};
