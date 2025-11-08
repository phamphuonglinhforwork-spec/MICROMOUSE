#include "controller.h"

Controller::Controller(MazeMap& map, Robot& r, FloodFill& ff): map(map), robot(r), ff(ff) {}

std::vector<std::pair<int,int>> Controller::centerCells() const {
    int N = map.size();
    if(N%2==0){
        int c = N/2;
        return { {c-1,c-1},{c-1,c},{c,c-1},{c,c} };
    } else {
        int c = N/2;
        return { {c,c} };
    }
}

void Controller::phaseExploreToCenter(){
    ff.setGoals(centerCells());
    pathPhase1.clear();
    int safety=0;
    while(!map.isCenter(robot.x(), robot.y()) && safety < 10000){
        map.at(robot.x(), robot.y()).cost = map.at(robot.x(), robot.y()).cost; // noop, preserve
        pathPhase1.push_back({robot.x(), robot.y()});
        robot.readSensorsAndUpdateWalls(map);
        ff.propagate();
        auto nxt = ff.nextStep(robot.x(), robot.y());
        if(nxt.first==robot.x() && nxt.second==robot.y()){
            // fallback: try neighbours
            const int dirs[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
            bool moved=false;
            for(auto &d:dirs){
                int nx=robot.x()+d[0], ny=robot.y()+d[1];
                if(map.inBounds(nx,ny) && !map.wallBetween(robot.x(),robot.y(),nx,ny)){
                    robot.moveTo({nx,ny});
                    moved=true;
                    break;
                }
            }
            if(!moved) break;
        } else {
            robot.moveTo(nxt);
        }
        safety++;
    }
}

void Controller::phaseReturnToStart(){
    int N = map.size();
    std::vector<std::vector<int>> penalty(N, std::vector<int>(N,0));
    for(auto &p: pathPhase1) penalty[p.second][p.first] = 1000;
    std::vector<std::pair<int,int>> startGoal = { {0,0} };
    // set penalty by temporarily adjusting costs: we'll implement simple approach - set start goal then propagate,
    // but use penalty by artificially increasing cost values before propagate: here we apply penalty to cells by setting cost high
    // then running propagate doesn't accept penalty; for simplicity, we mark penalized cells with a high cost initially
    map.resetCosts(99999);
    for(auto &g: startGoal) if(map.inBounds(g.first,g.second)) map.at(g.first,g.second).cost = 0;
    // apply penalty by setting penalized cells cost to a very large value (they'll be avoided if possible)
    for(int y=0;y<N;y++) for(int x=0;x<N;x++) if(penalty[y][x]) map.at(x,y).cost += penalty[y][x];
    ff.propagate();
    int safety=0;
    while(!(robot.x()==0 && robot.y()==0) && safety<10000){
        robot.readSensorsAndUpdateWalls(map);
        ff.propagate();
        auto nxt = ff.nextStep(robot.x(), robot.y());
        if(nxt.first==robot.x() && nxt.second==robot.y()){
            // fallback simple move
            const int dirs[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
            bool moved=false;
            for(auto &d:dirs){
                int nx=robot.x()+d[0], ny=robot.y()+d[1];
                if(map.inBounds(nx,ny) && !map.wallBetween(robot.x(),robot.y(),nx,ny)){
                    robot.moveTo({nx,ny});
                    moved=true;
                    break;
                }
            }
            if(!moved) break;
        } else {
            robot.moveTo(nxt);
        }
        safety++;
    }
}

void Controller::phaseSpeedRun(){
    ff.setGoals(centerCells());
    ff.propagate();
    auto path = ff.shortestPath(0,0);
    for(auto &step: path) robot.moveTo(step);
}
