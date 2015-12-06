/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include <cstdio>

#include "Elg/Clock/TimePoint.h"
#include "Elg/Clock/HighResolutionClock.h"

TEST(HighResolutionClock_Simple) {
  Elg::Clock::HighResolutionClock::TimePoint tstart = Elg::Clock::HighResolutionClock::Now();
  elg_float32 a = static_cast<elg_float32>(2.0);
  elg_float32 b = static_cast<elg_float32>(0.33);
  for (elg_uint32 x = 0;x < 1000000;++x) {
    a = a * b;
    b = a * a;
  }
  Elg::Clock::HighResolutionClock::TimePoint tend = Elg::Clock::HighResolutionClock::Now();

  fprintf(stderr, "Time it takes to do 2 * 10^6 loops of float32 multiplication is:\n");
  fprintf(stderr, "-> %lld ns\n", (tend - tstart).Count());
  fprintf(stderr, "-> Avg: %f ns\n", (tend - tstart).Count() / elg_float32(2000000));
  fprintf(stderr, "-> %lld us\n", Elg::Clock::DurationCast<Elg::Clock::Microseconds>(tend - tstart).Count());
  fprintf(stderr, "-> %lld ms\n", Elg::Clock::DurationCast<Elg::Clock::Milliseconds>(tend - tstart).Count());
  fprintf(stderr, "-> %lld s\n", Elg::Clock::DurationCast<Elg::Clock::Seconds>(tend - tstart).Count());
}
