#pragma once
#include <chrono>

using namespace std::chrono;

class Timer{
    public:
        Timer();
        ~Timer();

        void start();

        double get();
    private:
        time_point<steady_clock> base_time;
};