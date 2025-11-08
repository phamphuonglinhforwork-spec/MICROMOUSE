#include "robot.h"
#include "motion.h"

extern Motion motion;

Robot::Robot(): px(0), py(0), pd(NORTH) {}

int Robot::x() const { return px; }
int Robot::y() const { return py; }
Direction Robot::dir() const { return pd; }

void Robot::setState(int nx,int ny, Direction nd){ px=nx; py=ny; pd=nd; }

void Robot::readSensorsAndUpdateWalls(MazeMap& map){
    // Placeholder for sensor integration. In simulation, user can set map walls externally.
    // For hw, implement sensor reading and call map.setWall(...) accordingly.
}

Direction Robot::directionTo(const std::pair<int,int>& next) const {
    if(next.first > px) return EAST;
    if(next.first < px) return WEST;
    if(next.second > py) return NORTH;
    return SOUTH;
}

void Robot::rotateTo(Direction newDir){
    int diff = (int)newDir - (int)pd;
    if(diff < 0) diff += 4;
    if(diff == 1) motion.turnRight();
    else if(diff == 2) motion.turnBack();
    else if(diff == 3) motion.turnLeft();
    pd = newDir;
}

void Robot::moveTo(const std::pair<int,int>& next){
    Direction nd = directionTo(next);
    rotateTo(nd);
    motion.moveForward();
    px = next.first; py = next.second;
}
