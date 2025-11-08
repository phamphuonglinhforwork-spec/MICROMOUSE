#pragma once
#include "maze_map.h"
#include "robot.h"
#include "floodfill.h"
#include <vector>

class Controller {
public:
    Controller(MazeMap& map, Robot& r, FloodFill& ff);
    void phaseExploreToCenter();//Chạy lượt 1 về đích
    void phaseReturnToStart();//Chạy lại ví trí xuất phát với con đường khác đường đi ban đầu
    void phaseSpeedRun();//Speedrun tới đích
private:
    MazeMap& map;
    Robot& robot;
    FloodFill& ff;
    std::vector<std::pair<int,int>> pathPhase1;
    std::vector<std::pair<int,int>> centerCells() const;
};
