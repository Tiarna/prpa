#ifndef _PrPa_TP01_TIMER_HH_
#define _PrPa_TP01_TIMER_HH_

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

struct timer
{

  timer(double& s) : seconds(s), t0(steady_clock::now()) {}

  ~timer()
  {
    steady_clock::time_point      t1 = steady_clock::now();
    seconds = duration_cast<nanoseconds>(t1 - t0).count() / 1e9;
  }

  double&                       seconds;
  steady_clock::time_point      t0;
};

#endif
