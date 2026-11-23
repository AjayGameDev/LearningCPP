#pragma once
#include <chrono>

class Timer
{
  private:
          std::chrono::time_point<std::chrono::high_resolution_clock> startTime,endTime;
          std::chrono::duration<double,std::milli> elapsedTime{0.0};
  public:
          Timer();
          void startTimer();
          void endTimer();
          void printElapsedTime();
};




