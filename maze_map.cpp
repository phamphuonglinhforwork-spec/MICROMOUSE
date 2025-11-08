#include "maze_map.h"

MazeMap::MazeMap(int n): N(n), grid(n, std::vector<Cell>(n)) {}

int MazeMap::size() const { return N; }

void MazeMap::resetCosts(int largeValue) {
    for(int y=0;y<N;y++) for(int x=0;x<N;x++) grid[y][x].cost = largeValue;
}

bool MazeMap::inBounds(int x,int y) const { return x>=0 && y>=0 && x<N && y<N; }

Cell& MazeMap::at(int x,int y) { return grid[y][x]; }
const Cell& MazeMap::at(int x,int y) const { return grid[y][x]; }

void MazeMap::setWall(int x,int y, uint8_t wallBits){
    if(!inBounds(x,y)) return;
    grid[y][x].walls |= wallBits;
    // reciprocal: set neighbor wall if in bounds
    if((wallBits & 1) && inBounds(x,y+1)) grid[y+1][x].walls |= 4; // N -> neighbor S
    if((wallBits & 2) && inBounds(x+1,y)) grid[y][x+1].walls |= 8; // E -> neighbor W
    if((wallBits & 4) && inBounds(x,y-1)) grid[y-1][x].walls |= 1; // S -> neighbor N
    if((wallBits & 8) && inBounds(x-1,y)) grid[y][x-1].walls |= 2; // W -> neighbor E
}

bool MazeMap::wallBetween(int x,int y,int nx,int ny) const {
    if(!inBounds(x,y) || !inBounds(nx,ny)) return true;
    if(nx==x && ny==y+1) return (grid[y][x].walls & 1);
    if(nx==x+1 && ny==y) return (grid[y][x].walls & 2);
    if(nx==x && ny==y-1) return (grid[y][x].walls & 4);
    if(nx==x-1 && ny==y) return (grid[y][x].walls & 8);
    return true;
}

bool MazeMap::isCenter(int x,int y) const {
    if(N%2==0){
        int c = N/2;
        return (x==c-1 || x==c) && (y==c-1 || y==c);
    } else {
        int c = N/2;
        return x==c && y==c;
    }
}
