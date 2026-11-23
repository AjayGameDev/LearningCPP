#include "Timer.h"
#include <iostream>
#include <iomanip>

Timer::Timer()
{
  elapsedTime = std::chrono::duration<double,std::milli>(0.0);
}
void Timer::startTimer()
{
  startTime = std::chrono::high_resolution_clock::now();
}
void Timer::endTimer()
{
  endTime = std::chrono::high_resolution_clock::now();
  printElapsedTime();
}
void Timer::printElapsedTime()
{
  elapsedTime = endTime - startTime;
  std::cout << std::fixed << std::setprecision(2) << "Elapsed time: " << elapsedTime.count() << " ms" << "\n";
}
