#pragma once
#include <utility>
#include "maze_map.h"

enum Direction { NORTH=0, EAST=1, SOUTH=2, WEST=3 };

class Robot {
public:
    Robot();
    int x() const;
    int y() const;
    Direction dir() const;
    void setState(int nx,int ny, Direction nd);
    void readSensorsAndUpdateWalls(MazeMap& map); // to be implemented for sim/hw
    void moveTo(const std::pair<int,int>& next); // rotate+move using Motion interface
private:
    int px, py;
    Direction pd;
    Direction directionTo(const std::pair<int,int>& next) const;
    void rotateTo(Direction newDir);
};
