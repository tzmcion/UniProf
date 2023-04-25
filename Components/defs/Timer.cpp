#include "../Timer.h"

Timer::Timer(){}

Timer::~Timer(){}

void Timer::start(){
    base_time = std::chrono::steady_clock::now();
}

double Timer::get(){
    std::chrono::time_point<steady_clock> end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<milliseconds>(end - base_time).count();
}