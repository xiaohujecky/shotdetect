/**
 * @file   main.cpp
 * @author yuhonglin <yuhonglin1986@gmail.com>
 * @date   Fri Mar 28 11:06:01 2014
 *
 * @brief  short detection program
 *
 *
 */

#include "shotdetector.hpp"
#include "logger.hpp"
#include "tools.hpp"

int main(int argc, char *argv[]) {

  Clock::time_point start = Clock::now();
  ShotDetector sd(argv, argc);

  sd.run();
  print_elapsed_time(start, "Shot detection:");

  sd.outputKeyFrame();

  print_elapsed_time(start, "Shot-Keyframe:");
  return 0;
}
