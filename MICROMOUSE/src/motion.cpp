#include "motion.h"
#include <thread>
#include <chrono>

void Motion::moveForward(){ std::this_thread::sleep_for(std::chrono::milliseconds(200)); }
void Motion::turnLeft(){ std::this_thread::sleep_for(std::chrono::milliseconds(120)); }
void Motion::turnRight(){ std::this_thread::sleep_for(std::chrono::milliseconds(120)); }
void Motion::turnBack(){ turnRight(); turnRight(); }
void Motion::stop() {}
