#include "myfill.h"
#include <vector>

static void _MyFill(std::vector<std::vector<bool>>& arr, int x, int y, int width, int height);
static void MyFillCore(std::vector<std::vector<bool>>& arr, int x, int y, int width, int height);

void MyFill(std::vector<std::vector<bool>>& arr, int x, int y){
    if(!arr[y][x]) _MyFill(arr, x, y, (int)arr[0].size(), (int)arr.size());
}

static void _MyFill(std::vector<std::vector<bool>>& arr, int x, int y, int width, int height){
    // move up and left as far as possible (preference to up)
    while(true){
        int ox = x, oy = y;
        while(y != 0 && !arr[y-1][x]) y--;
        while(x != 0 && !arr[y][x-1]) x--;
        if(x == ox && y == oy) break;
    }
    MyFillCore(arr, x, y, width, height);
}

static void MyFillCore(std::vector<std::vector<bool>>& arr, int x, int y, int width, int height){
    int lastRowLength = 0;
    do {
        int rowLength = 0, sx = x;
        if(lastRowLength != 0 && arr[y][x]){
            do {
                if(--lastRowLength == 0) return;
            } while(arr[y][++x]);
            sx = x;
        } else {
            for(; x != 0 && !arr[y][x-1]; rowLength++, lastRowLength++){
                arr[y][--x] = true;
                if(y != 0 && !arr[y-1][x]) _MyFill(arr, x, y-1, width, height);
            }
        }

        for(; sx < width && !arr[y][sx]; rowLength++, sx++) arr[y][sx] = true;

        if(rowLength < lastRowLength){
            for(int end = x + lastRowLength; ++sx < end; ){
                if(!arr[y][sx]) MyFillCore(arr, sx, y, width, height);
            }
        } else if(rowLength > lastRowLength && y != 0){
            for(int ux = x + lastRowLength; ++ux < sx; ){
                if(!arr[y-1][ux]) _MyFill(arr, ux, y-1, width, height);
            }
        }
        lastRowLength = rowLength;
    } while(lastRowLength != 0 && ++y < height);
}
