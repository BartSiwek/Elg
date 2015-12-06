/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_PERFORMANCE_SCOPEPROFILER_H_
#define ELG_PERFORMANCE_SCOPEPROFILER_H_

#include <cstdio>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/StringHash/Hash.h"
#include "Elg/Clock/HighResolutionClock.h"

// Define ELG_SCOPE_PROFILING to enable scope profiling, undefine to disable profiling
#ifdef ELG_SCOPE_PROFILING
#define ELG_PROFILE_NAMED_SCOPE(SCOPE_ID)                                                                             \
  Elg::Performance::Scope::ScopeProfiler ScopeProfiler##__LINE__(ELG_STRING_HASH(SCOPE_ID), SCOPE_ID)
#define ELG_PROFILE_SCOPE                                                                                             \
  ELG_PROFILE_NAMED_SCOPE(ELG_FUNC)
#define ELG_PROFILER_DUMP(OUTPUT)                                                                                     \
  Elg::Performance::Scope::DumpStatistics(OUTPUT)
#else
#define ELG_PROFILE_NAMED_SCOPE(SCOPE_ID)
#define ELG_PROFILE_SCOPE
#define ELG_PROFILER_DUMP(OUTPUT)
#endif

// The actual code
namespace Elg {
namespace Performance {
namespace Scope {

// The profiler interface
void EnterScope(elg_uint32 scope_id_hash, const char* scope_id);
void LeaveScope(elg_uint64 time);
void DumpStatistics(FILE* output);

// Helper class
class ScopeProfiler {
 public:
  ELG_FORCEINLINE ScopeProfiler(elg_uint32 scope_id_hash, const char* scope_id) {
    using Elg::Clock::HighResolutionClock;

    EnterScope(scope_id_hash, scope_id);
    m_start_time_ = HighResolutionClock::TimeSinceEpoch();
  }

  ELG_FORCEINLINE ~ScopeProfiler() {
    using Elg::Clock::HighResolutionClock;

    elg_uint64 end_time = HighResolutionClock::TimeSinceEpoch();
    LeaveScope(end_time - m_start_time_);
  }

 private:
  elg_uint64 m_start_time_;
};

}  // namespace Scope
}  // namespace Performance
}  // namespace Elg

#endif  // ELG_PERFORMANCE_SCOPEPROFILER_H_
