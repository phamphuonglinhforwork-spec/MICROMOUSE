#pragma once
#include <vector>

// MyFill: scanline-style region fill (translated from C# snippet).
// Works on a boolean grid: true = filled/blocked, false = clear.
// This API flips cells to true as it fills the contiguous region starting at (x,y).
void MyFill(std::vector<std::vector<bool>>& arr, int x, int y);
