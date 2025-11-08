#pragma once
#include "maze_map.h"
#include <vector>
#include <utility>

class FloodFill {
public:
    FloodFill(MazeMap& m);
    // set goals and run propagate
    void setGoals(const std::vector<std::pair<int,int>>& goals);
    void propagate(); // uses optimized scanline-style propagation
    std::pair<int,int> nextStep(int x,int y) const;
    std::vector<std::pair<int,int>> shortestPath(int sx,int sy) const;
private:
    MazeMap& maze;
};
