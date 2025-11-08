#include "floodfill.h"
#include <queue>
#include <limits>
#include <vector>

FloodFill::FloodFill(MazeMap& m): maze(m) {}

void FloodFill::setGoals(const std::vector<std::pair<int,int>>& goals){
    maze.resetCosts(99999);
    for(auto &g: goals){
        if(maze.inBounds(g.first,g.second)){
            maze.at(g.first,g.second).cost = 0;
        }
    }
}

// Optimized propagation inspired by scanline fill. This keeps correctness of classic floodfill
// while trying to expand contiguous segments horizontally to reduce queue churn.
void FloodFill::propagate(){
    int N = maze.size();
    std::queue<std::pair<int,int>> q;
    // enqueue all zero-cost cells
    for(int y=0;y<N;y++) for(int x=0;x<N;x++) if(maze.at(x,y).cost==0) q.push({x,y});

    while(!q.empty()){
        auto [cx,cy] = q.front(); q.pop();
        int base = maze.at(cx,cy).cost;
        // four directions
        const int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        for(auto &d: dirs){
            int nx = cx + d[0], ny = cy + d[1];
            if(!maze.inBounds(nx,ny)) continue;
            if(maze.wallBetween(cx,cy,nx,ny)) continue;
            if(maze.at(nx,ny).cost > base + 1){
                maze.at(nx,ny).cost = base + 1;
                // perform horizontal scanline expansion on the row 'ny' around nx
                // expand left
                int lx = nx - 1;
                while(lx >= 0 && !maze.wallBetween(lx,ny,lx+1,ny) && maze.at(lx,ny).cost > base + 2){
                    maze.at(lx,ny).cost = base + 2;
                    q.push({lx,ny});
                    lx--;
                }
                // expand right
                int rx = nx + 1;
                while(rx < N && !maze.wallBetween(rx-1,ny,rx,ny) && maze.at(rx,ny).cost > base + 2){
                    maze.at(rx,ny).cost = base + 2;
                    q.push({rx,ny});
                    rx++;
                }
                q.push({nx,ny});
            }
        }
    }
}

std::pair<int,int> FloodFill::nextStep(int x,int y) const {
    int bestCost = std::numeric_limits<int>::max();
    std::pair<int,int> best = {x,y};
    const int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    for(auto &d: dirs){
        int nx = x + d[0], ny = y + d[1];
        if(!maze.inBounds(nx,ny)) continue;
        if(maze.wallBetween(x,y,nx,ny)) continue;
        if(maze.at(nx,ny).cost < bestCost){
            bestCost = maze.at(nx,ny).cost;
            best = {nx,ny};
        }
    }
    return best;
}

std::vector<std::pair<int,int>> FloodFill::shortestPath(int sx,int sy) const {
    std::vector<std::pair<int,int>> path;
    int x = sx, y = sy;
    int safety = maze.size()*maze.size()*4;
    while(!maze.isCenter(x,y) && safety-->0){
        auto nxt = nextStep(x,y);
        if(nxt.first==x && nxt.second==y) break;
        path.push_back(nxt);
        x = nxt.first; y = nxt.second;
    }
    return path;
}
