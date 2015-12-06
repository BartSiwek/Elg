/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Clock/TimePoint.h"
#include "Elg/Clock/HighResolutionClock.h"

#define ELG_SCOPE_PROFILING  // We need this for scope profiling tests
#include "Elg/Performance/ScopeProfiler.h"

TEST(ScopeProfilerOverhead) {
  // Times to loop
  const elg_uint32 MAX_LOOPS = 1000000;
  elg_float32 a;
  elg_float32 b;

  // No profiling run
  a = static_cast<elg_float32>(2.0);
  b = static_cast<elg_float32>(0.33);

  Elg::Clock::HighResolutionClock::TimePoint pure_start = Elg::Clock::HighResolutionClock::Now();
  for (elg_uint32 x = 0;x < MAX_LOOPS;++x) {
    a = a * b;
    b = a * a;
  }
  Elg::Clock::HighResolutionClock::TimePoint pure_end = Elg::Clock::HighResolutionClock::Now();

  // Profiling enabled run
  a = static_cast<elg_float32>(2.0);
  b = static_cast<elg_float32>(0.33);
  Elg::Clock::HighResolutionClock::TimePoint profiled_start = Elg::Clock::HighResolutionClock::Now();
  for (elg_uint32 x = 0;x < MAX_LOOPS;++x) {
    ELG_PROFILE_SCOPE;
    a = a * b;
    b = a * a;
  }
  Elg::Clock::HighResolutionClock::TimePoint profiled_end = Elg::Clock::HighResolutionClock::Now();

  // Time it took
  Elg::Clock::HighResolutionClock::Duration pure_time = pure_end - pure_start;
  Elg::Clock::HighResolutionClock::Duration profiled_time = profiled_end - profiled_start;
  Elg::Clock::HighResolutionClock::Duration overhead_time = profiled_time - pure_time;
  Elg::Clock::HighResolutionClock::Duration avg_overhead_time = overhead_time / MAX_LOOPS;

  // Print the results
  fprintf(stderr, "Profiling parameters:\n");
  fprintf(stderr, "Pure time: %lld ns\n", pure_time.Count());
  fprintf(stderr, "Profiled time: %lld ns\n", profiled_time.Count());
  fprintf(stderr, "Overhead time: %lld ns\n", overhead_time.Count());
  fprintf(stderr, "Avg overhead time: %lld ns\n", avg_overhead_time.Count());
}

elg_uint32 CommonGrandchild() {
  ELG_PROFILE_SCOPE;
  static elg_uint32 x = 0;
  return ++x;
}

elg_uint32 LeftChild() {
  ELG_PROFILE_SCOPE;
  elg_uint32 result = CommonGrandchild() - CommonGrandchild();
  return result;
}

elg_uint32 RightChild() {
  ELG_PROFILE_SCOPE;
  elg_uint32 result = CommonGrandchild() * CommonGrandchild();
  return result;
}

elg_uint32 Root() {
  ELG_PROFILE_SCOPE;
  elg_uint32 result = LeftChild() + RightChild();
  return result;
}

TEST(ScopeProfilerHierarchy) {
  Root();
  Elg::Performance::Scope::DumpStatistics(stdout);
}

int Recurse(int x) {
  ELG_PROFILE_SCOPE;
  if (x >= 10) {
    return x;
  }
  return x * Recurse(x+1);
}

TEST(ScopeProfilerRecursive) {
  Recurse(1);
  Elg::Performance::Scope::DumpStatistics(stdout);
}
