/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

#include "Elg/Utilities/ETL/Memory.h"

// Helper types
template<typename T>
struct CallConstructor {
  static void Exec(T* ptr) {
    ::new(ptr) T;
  }
};

template<typename T>
struct CallDestructor {
  static void Exec(T* ptr) {
    ptr->~T();
  }
};

// Tests
TEST(Etl_Memory_UninitializedMoveStartCommitAbort_Throwing) {
  // Helper structs
  struct NonPodType {
    enum ObjectState {
      OBJECT_STATE_CONSTRUCTED = 1,
      OBJECT_STATE_COPY_CONSTRUCTED = 2,
      OBJECT_STATE_DESTROYED = 3,
    };

    NonPodType() : ShouldThrowOnCopy(false), State(OBJECT_STATE_CONSTRUCTED) {
    }

    NonPodType(const NonPodType& other) : ShouldThrowOnCopy(other.ShouldThrowOnCopy),
                                          State(OBJECT_STATE_COPY_CONSTRUCTED) {
      if (ShouldThrowOnCopy) {
        throw std::exception("Test exception");
      }
    }

    ~NonPodType() {
      State = OBJECT_STATE_DESTROYED;
    }

    bool ShouldThrowOnCopy;
    ObjectState State;
  };

  // 1. Move a POD type - they do not throw exception but this scenario needs to be tested too
  elg_int32 pod_source[3] = {1, 2, 3};
  elg_int32 pod_dest[3];
  Elg::Utilities::Etl::uninitialized_move_start(pod_source, pod_source + 3, pod_dest);
  Elg::Utilities::Etl::uninitialized_move_commit(pod_source, pod_source + 3, pod_dest);

  CHECK_EQUAL(1, pod_dest[0]);
  CHECK_EQUAL(2, pod_dest[1]);
  CHECK_EQUAL(3, pod_dest[2]);

  // 2. Move a non-POD type without exception
  NonPodType nothrowning_scenario_nonpod_source[3];
  NonPodType nothrowning_scenario_nonpod_dest[3];

  bool nothrowning_scenario_was_exception_thrown = false;
  try {
    Elg::Utilities::Etl::uninitialized_move_start(nothrowning_scenario_nonpod_source,
                                                  nothrowning_scenario_nonpod_source + 3,
                                                  nothrowning_scenario_nonpod_dest);
    Elg::Utilities::Etl::uninitialized_move_commit(nothrowning_scenario_nonpod_source,
                                                   nothrowning_scenario_nonpod_source + 3,
                                                   nothrowning_scenario_nonpod_dest);
  } catch(...) {
    nothrowning_scenario_was_exception_thrown = true;
  }

  CHECK_EQUAL(false, nothrowning_scenario_was_exception_thrown);

  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, nothrowning_scenario_nonpod_source[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, nothrowning_scenario_nonpod_source[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, nothrowning_scenario_nonpod_source[2].State);

  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, nothrowning_scenario_nonpod_dest[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, nothrowning_scenario_nonpod_dest[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, nothrowning_scenario_nonpod_dest[2].State);

  // 3. Move a non-POD type with exception
  NonPodType throwning_scenario_nonpod_source[3];
  NonPodType throwning_scenario_nonpod_dest[3];  // All X set to zero

  throwning_scenario_nonpod_source[1].ShouldThrowOnCopy = true;  // Make it throw and exception

  bool throwning_scenario_was_exception_thrown = false;
  try {
    Elg::Utilities::Etl::uninitialized_move_start(throwning_scenario_nonpod_source,
                                                  throwning_scenario_nonpod_source + 3,
                                                  throwning_scenario_nonpod_dest);
    Elg::Utilities::Etl::uninitialized_move_commit(throwning_scenario_nonpod_source,
                                                   throwning_scenario_nonpod_source + 3,
                                                   throwning_scenario_nonpod_dest);
  } catch(...) {
    throwning_scenario_was_exception_thrown = true;
  }

  CHECK_EQUAL(true, throwning_scenario_was_exception_thrown);

  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, throwning_scenario_nonpod_source[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, throwning_scenario_nonpod_source[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, throwning_scenario_nonpod_source[2].State);

  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, throwning_scenario_nonpod_dest[0].State);         // Both called
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, throwning_scenario_nonpod_dest[1].State);  // No destr called
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, throwning_scenario_nonpod_dest[2].State);       // No constr called
}

TEST(Etl_Memory_UninitializedMoveStartCommitAbort_NotThrowing) {
  // Helper structs
  struct NonPodType {
    enum ObjectState {
      OBJECT_STATE_CONSTRUCTED = 1,
      OBJECT_STATE_COPY_CONSTRUCTED = 2,
      OBJECT_STATE_DESTROYED = 3,
    };

    NonPodType() : ShouldFailOnCopy(false), IsValid(true), State(OBJECT_STATE_CONSTRUCTED) {
    }

    NonPodType(const NonPodType& other) : ShouldFailOnCopy(other.ShouldFailOnCopy), IsValid(true),
                                          State(OBJECT_STATE_COPY_CONSTRUCTED) {
       if (ShouldFailOnCopy) {
         IsValid = false;
       }
    }

    ~NonPodType() {
      State = OBJECT_STATE_DESTROYED;
    }

    bool ShouldFailOnCopy;
    bool IsValid;
    ObjectState State;
  };

  // 1. Move a POD type - they do not throw and cannot fail
  elg_int32 pod_source[3] = {1, 2, 3};
  elg_int32 pod_dest[3];
  Elg::Utilities::Etl::uninitialized_move_start_nothrow(pod_source, pod_source + 3, pod_dest);
  Elg::Utilities::Etl::uninitialized_move_commit(pod_source, pod_source + 3, pod_dest);

  CHECK_EQUAL(1, pod_dest[0]);
  CHECK_EQUAL(2, pod_dest[1]);
  CHECK_EQUAL(3, pod_dest[2]);

  // 2. Move a non-POD type with success
  NonPodType notfailing_scenario_nonpod_source[3];
  NonPodType notfailing_scenario_nonpod_dest[3];

  Elg::Utilities::Etl::uninitialized_move_start_nothrow(notfailing_scenario_nonpod_source,
                                                        notfailing_scenario_nonpod_source + 3,
                                                        notfailing_scenario_nonpod_dest);

  // Test state mid-move
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, notfailing_scenario_nonpod_source[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, notfailing_scenario_nonpod_source[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, notfailing_scenario_nonpod_source[2].State);

  CHECK_EQUAL(true, notfailing_scenario_nonpod_dest[0].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, notfailing_scenario_nonpod_dest[0].State);
  CHECK_EQUAL(true, notfailing_scenario_nonpod_dest[1].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, notfailing_scenario_nonpod_dest[1].State);
  CHECK_EQUAL(true, notfailing_scenario_nonpod_dest[2].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, notfailing_scenario_nonpod_dest[2].State);

  // We know (by magic.. and test design) that we should commit
  Elg::Utilities::Etl::uninitialized_move_commit(notfailing_scenario_nonpod_source,
                                                 notfailing_scenario_nonpod_source + 3,
                                                 notfailing_scenario_nonpod_dest);

  // Test state after move
  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, notfailing_scenario_nonpod_source[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, notfailing_scenario_nonpod_source[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, notfailing_scenario_nonpod_source[2].State);

  CHECK_EQUAL(true, notfailing_scenario_nonpod_dest[0].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, notfailing_scenario_nonpod_dest[0].State);
  CHECK_EQUAL(true, notfailing_scenario_nonpod_dest[1].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, notfailing_scenario_nonpod_dest[1].State);
  CHECK_EQUAL(true, notfailing_scenario_nonpod_dest[2].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, notfailing_scenario_nonpod_dest[2].State);

  // 3. Move a non-POD type with failure
  NonPodType failing_scenario_nonpod_source[3];
  NonPodType failing_scenario_nonpod_dest[3];

  failing_scenario_nonpod_source[1].ShouldFailOnCopy = true;  // Make it throw and exception

  Elg::Utilities::Etl::uninitialized_move_start_nothrow(failing_scenario_nonpod_source,
                                                        failing_scenario_nonpod_source + 3,
                                                        failing_scenario_nonpod_dest);

  // Test state mid-move
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, failing_scenario_nonpod_source[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, failing_scenario_nonpod_source[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, failing_scenario_nonpod_source[2].State);

  CHECK_EQUAL(true, failing_scenario_nonpod_dest[0].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, failing_scenario_nonpod_dest[0].State);
  CHECK_EQUAL(false, failing_scenario_nonpod_dest[1].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, failing_scenario_nonpod_dest[1].State);
  CHECK_EQUAL(true, failing_scenario_nonpod_dest[2].IsValid);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, failing_scenario_nonpod_dest[2].State);

  // We know (by magic, and test design) that we should abort
  Elg::Utilities::Etl::uninitialized_move_abort(failing_scenario_nonpod_source,
                                                failing_scenario_nonpod_source + 3,
                                                failing_scenario_nonpod_dest);

  // Test state after move
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, failing_scenario_nonpod_source[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, failing_scenario_nonpod_source[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, failing_scenario_nonpod_source[2].State);

  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, failing_scenario_nonpod_dest[0].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, failing_scenario_nonpod_dest[1].State);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_DESTROYED, failing_scenario_nonpod_dest[2].State);
}

TEST(Etl_Memory_UninitializedCopy) {
  // Helper structs
  struct NonPodType {
    enum ObjectState {
      OBJECT_STATE_CONSTRUCTED = 1,
      OBJECT_STATE_COPY_CONSTRUCTED = 2,
      OBJECT_STATE_DESTROYED = 3,
    };

    explicit NonPodType(elg_int32 x) : X(x), State(OBJECT_STATE_CONSTRUCTED) {
    }

    NonPodType(const NonPodType& other) : X(other.X), State(OBJECT_STATE_COPY_CONSTRUCTED) {
    }

    ~NonPodType() {
      State = OBJECT_STATE_DESTROYED;
    }

    elg_int32 X;
    ObjectState State;
  };

  // POD type
  elg_int32 pod_source[3] = {1, 2, 3};
  elg_int32 pod_dest[3];
  elg_int32* pod_result;

  pod_result = Elg::Utilities::Etl::uninitialized_copy(pod_source, pod_source + 3, pod_dest);

  CHECK(pod_result == pod_dest + 3);
  CHECK_EQUAL(1, pod_dest[0]);
  CHECK_EQUAL(2, pod_dest[1]);
  CHECK_EQUAL(3, pod_dest[2]);

  // Non-POD type
  NonPodType nonpod_source[3] = {NonPodType(1), NonPodType(2), NonPodType(3)};
  NonPodType nonpod_dest[3] = {NonPodType(0), NonPodType(0), NonPodType(0)};
  NonPodType* nonpod_result;

  nonpod_result = Elg::Utilities::Etl::uninitialized_copy(nonpod_source, nonpod_source + 3, nonpod_dest);

  CHECK_EQUAL(1, nonpod_source[0].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_source[0].State);
  CHECK_EQUAL(2, nonpod_source[1].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_source[1].State);
  CHECK_EQUAL(3, nonpod_source[2].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_source[2].State);

  CHECK(nonpod_result == nonpod_dest + 3);
  CHECK_EQUAL(1, nonpod_dest[0].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, nonpod_dest[0].State);
  CHECK_EQUAL(2, nonpod_dest[1].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, nonpod_dest[1].State);
  CHECK_EQUAL(3, nonpod_dest[2].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_COPY_CONSTRUCTED, nonpod_dest[2].State);
}

TEST(Etl_Memory_UninitializedCopyPointer) {
  // POD type
  elg_int32 pod_source[3] = {1, 2, 3};
  elg_int32 pod_dest[3];
  elg_int32* result;

  result = Elg::Utilities::Etl::uninitialized_copy_ptr(pod_source, pod_source + 3, pod_dest);

  CHECK(result == pod_dest + 3);
  CHECK_EQUAL(1, pod_dest[0]);
  CHECK_EQUAL(2, pod_dest[1]);
  CHECK_EQUAL(3, pod_dest[2]);
}

TEST(Etl_Memory_UninitializedFill) {
  // Helper structs
  struct NonPodType {
    enum ObjectState {
      OBJECT_STATE_CONSTRUCTED = 1,
      OBJECT_STATE_COPY_CONSTRUCTED = 2,
      OBJECT_STATE_DESTROYED = 3,
    };

    explicit NonPodType(elg_int32 x) : X(x), State(OBJECT_STATE_CONSTRUCTED) {
    }

    NonPodType(const NonPodType& other) : X(other.X), State(OBJECT_STATE_COPY_CONSTRUCTED) {
    }

    ~NonPodType() {
      State = OBJECT_STATE_DESTROYED;
    }

    elg_int32 X;
    ObjectState State;
  };

  // POD type
  elg_int32 pod_dest[3];
  Elg::Utilities::Etl::uninitialized_fill(pod_dest, pod_dest + 3, 123);

  CHECK_EQUAL(123, pod_dest[0]);
  CHECK_EQUAL(123, pod_dest[1]);
  CHECK_EQUAL(123, pod_dest[2]);

  // Non-POD type
  NonPodType nonpod_dest[3] = {NonPodType(0), NonPodType(0), NonPodType(0)};
  Elg::Utilities::Etl::uninitialized_fill(nonpod_dest, nonpod_dest + 3, NonPodType(123));

  CHECK_EQUAL(123, nonpod_dest[0].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[0].State);
  CHECK_EQUAL(123, nonpod_dest[1].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[1].State);
  CHECK_EQUAL(123, nonpod_dest[2].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[2].State);
}

TEST(Etl_Memory_UninitializedFillPtr) {
  elg_int32 pod_dest[3];
  Elg::Utilities::Etl::uninitialized_fill_ptr(pod_dest, pod_dest + 3, 123);

  CHECK_EQUAL(123, pod_dest[0]);
  CHECK_EQUAL(123, pod_dest[1]);
  CHECK_EQUAL(123, pod_dest[2]);
}

TEST(Etl_Memory_UninitializedFillN) {
  // Helper structs
  struct NonPodType {
    enum ObjectState {
      OBJECT_STATE_CONSTRUCTED = 1,
      OBJECT_STATE_COPY_CONSTRUCTED = 2,
      OBJECT_STATE_DESTROYED = 3,
    };

    explicit NonPodType(elg_int32 x) : X(x), State(OBJECT_STATE_CONSTRUCTED) {
    }

    NonPodType(const NonPodType& other) : X(other.X), State(OBJECT_STATE_COPY_CONSTRUCTED) {
    }

    ~NonPodType() {
      State = OBJECT_STATE_DESTROYED;
    }

    elg_int32 X;
    ObjectState State;
  };

  // POD type
  elg_int32 pod_dest[5] = {0, 0, 0, 0, 0};
  Elg::Utilities::Etl::uninitialized_fill_n(pod_dest, 3, 123);

  CHECK_EQUAL(123, pod_dest[0]);
  CHECK_EQUAL(123, pod_dest[1]);
  CHECK_EQUAL(123, pod_dest[2]);
  CHECK_EQUAL(0, pod_dest[3]);
  CHECK_EQUAL(0, pod_dest[4]);

  // Non-POD type
  NonPodType nonpod_dest[5] = {NonPodType(0), NonPodType(0), NonPodType(0), NonPodType(0), NonPodType(0)};
  Elg::Utilities::Etl::uninitialized_fill_n(nonpod_dest, 3, NonPodType(123));

  CHECK_EQUAL(123, nonpod_dest[0].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[0].State);
  CHECK_EQUAL(123, nonpod_dest[1].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[1].State);
  CHECK_EQUAL(123, nonpod_dest[2].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[2].State);
  CHECK_EQUAL(0, nonpod_dest[3].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[3].State);
  CHECK_EQUAL(0, nonpod_dest[4].X);
  CHECK_EQUAL(NonPodType::OBJECT_STATE_CONSTRUCTED, nonpod_dest[4].State);
}

TEST(Etl_Memory_UninitializedFillNPtr) {
  elg_int32 pod_dest[5] = {0, 0, 0, 0, 0};
  Elg::Utilities::Etl::uninitialized_fill_n_ptr(pod_dest, 3, 123);

  CHECK_EQUAL(123, pod_dest[0]);
  CHECK_EQUAL(123, pod_dest[1]);
  CHECK_EQUAL(123, pod_dest[2]);
  CHECK_EQUAL(0, pod_dest[3]);
  CHECK_EQUAL(0, pod_dest[4]);
}

TEST(Etl_Memory_UninitializedCopyFill) {
  elg_int32 pod_source[3] = {1, 2, 3};
  elg_int32 pod_dest[6] = {0, 0, 0, 0, 0, 0};
  Elg::Utilities::Etl::uninitialized_copy_fill(pod_source, pod_source + 3, pod_dest, pod_dest + 6, 123);

  CHECK_EQUAL(1, pod_dest[0]);
  CHECK_EQUAL(2, pod_dest[1]);
  CHECK_EQUAL(3, pod_dest[2]);
  CHECK_EQUAL(123, pod_dest[3]);
  CHECK_EQUAL(123, pod_dest[4]);
  CHECK_EQUAL(123, pod_dest[5]);
}

TEST(Etl_Memory_UninitializedFillCopy) {
  elg_int32 pod_source[3] = {1, 2, 3};
  elg_int32 pod_dest[6] = {0, 0, 0, 0, 0, 0};
  Elg::Utilities::Etl::uninitialized_fill_copy(pod_dest, pod_dest + 2, 123, pod_source, pod_source + 3);

  CHECK_EQUAL(123, pod_dest[0]);
  CHECK_EQUAL(123, pod_dest[1]);
  CHECK_EQUAL(1, pod_dest[2]);
  CHECK_EQUAL(2, pod_dest[3]);
  CHECK_EQUAL(3, pod_dest[4]);
  CHECK_EQUAL(0, pod_dest[5]);
}

TEST(Etl_Memory_UninitializedCopyCopy) {
  elg_int32 pod_source1[3] = {1, 2, 3};
  elg_int32 pod_source2[2] = {-3, -2};
  elg_int32 pod_dest[6] = {0, 0, 0, 0, 0, 0};
  Elg::Utilities::Etl::uninitialized_copy_copy(pod_source1, pod_source1 + 3, pod_source2, pod_source2 + 2, pod_dest);

  CHECK_EQUAL(1, pod_dest[0]);
  CHECK_EQUAL(2, pod_dest[1]);
  CHECK_EQUAL(3, pod_dest[2]);
  CHECK_EQUAL(-3, pod_dest[3]);
  CHECK_EQUAL(-2, pod_dest[4]);
  CHECK_EQUAL(0, pod_dest[5]);
}

TEST(Etl_Memory_Destruct) {
  struct NonTrivialDestructorType {
    enum ObjectState {
      OBJECT_STATE_CONSTRUCTED = 1,
      OBJECT_STATE_DESTROYED = 2,
    };

    NonTrivialDestructorType() : State(OBJECT_STATE_CONSTRUCTED) {
    }

    ~NonTrivialDestructorType() {
      State = OBJECT_STATE_DESTROYED;
    }

    ObjectState State;
  };

  NonTrivialDestructorType obj;
  Elg::Utilities::Etl::destruct(&obj);
  CHECK_EQUAL(NonTrivialDestructorType::OBJECT_STATE_DESTROYED, obj.State);
}

TEST(Etl_Memory_) {
  struct NonTrivialDestructorType {
    enum ObjectState {
      OBJECT_STATE_CONSTRUCTED = 1,
      OBJECT_STATE_DESTROYED = 2,
    };

    NonTrivialDestructorType() : State(OBJECT_STATE_CONSTRUCTED) {
    }

    ~NonTrivialDestructorType() {
      State = OBJECT_STATE_DESTROYED;
    }

    ObjectState State;
  };

  // Trivial destructor types (testing this to see if it actually gets called)
  elg_int32 trivial[3] = {1, 2, 3};
  Elg::Utilities::Etl::destruct(trivial, trivial + 3);

  // Non-trivial destructor types
  NonTrivialDestructorType nontrivial[3];
  Elg::Utilities::Etl::destruct(nontrivial, nontrivial + 3);
  CHECK_EQUAL(NonTrivialDestructorType::OBJECT_STATE_DESTROYED, nontrivial[0].State);
  CHECK_EQUAL(NonTrivialDestructorType::OBJECT_STATE_DESTROYED, nontrivial[1].State);
  CHECK_EQUAL(NonTrivialDestructorType::OBJECT_STATE_DESTROYED, nontrivial[2].State);
}
