#include "maze_map.h"
#include "robot.h"
#include "floodfill.h"
#include "motion.h"
#include "controller.h"

Motion motion;

// chạy test
static void buildSample(MazeMap& m){
    int N = m.size();
    for(int i=0;i<N;i++){
        m.setWall(i,0,4); // south walls
        m.setWall(i,N-1,1); // north walls
        m.setWall(0,i,8); // west walls
        m.setWall(N-1,i,2); // east walls
    }
    m.setWall(1,0,1);
    m.setWall(1,1,2);
    m.setWall(2,1,1);
}

int main(){
    MazeMap map(16);
    buildSample(map);
    Robot robot;
    FloodFill ff(map);
    Controller ctrl(map, robot, ff);

    // phase 1
    ctrl.phaseExploreToCenter();
    // phase 2
    ctrl.phaseReturnToStart();
    // phase 3
    ctrl.phaseSpeedRun();

    motion.stop();
    return 0;
}
