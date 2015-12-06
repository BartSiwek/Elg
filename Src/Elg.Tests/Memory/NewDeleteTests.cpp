/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

#include "Elg/Memory/Memory.h"

// Test helper classes
struct TestAllocator {
  enum LastCallType {
    LAST_CALL_NONE = 0,
    LAST_CALL_ALLOCATE = 1,
    LAST_CALL_FREE = 2,
  };

  TestAllocator()
      : SimulateOutOfMemory(false), LastCall(LAST_CALL_NONE), Size(0), Align(0), Pointer(NULL) {
  }

  explicit TestAllocator(bool simulate_out_of_memory)
      : SimulateOutOfMemory(simulate_out_of_memory), LastCall(LAST_CALL_NONE), Size(0), Align(0), Pointer(NULL) {
  }

  void* Allocate(elg_size_type size, elg_size_type align, const char* /* file */, elg_uint32 /* line */) {
    LastCall = LAST_CALL_ALLOCATE;
    Size = size;
    Align = align;

    if (!SimulateOutOfMemory) {
      return std::malloc(size);
    } else {
      return NULL;
    }
  }

  void Free(void* ptr, const char* /* file */, elg_uint32 /* line */) {
    LastCall = LAST_CALL_FREE;
    Pointer = ptr;

    std::free(ptr);
  }

  bool SimulateOutOfMemory;
  LastCallType LastCall;
  elg_size_type Size;
  elg_size_type Align;
  void* Pointer;
};

struct TestType {
  static const elg_uint32 MAX_INSTANCES = 100;

  TestType() {
    if (NextId < MAX_INSTANCES) {
      InstanceId = NextId;
      ++NextId;

      WasConstructorCalled[InstanceId] = true;
    } else {
      throw std::logic_error("Attempt to create more than MAX_INSTANCES of TestType");
    }
  }

  ~TestType() {
    WasDestructorCalled[InstanceId] = true;
  }

  // The static functions
  static void ClearInstanceStates() {
    NextId = 0;
    for (elg_uint32 instance_id = 0; instance_id < MAX_INSTANCES; ++instance_id) {
      WasConstructorCalled[instance_id] = false;
    }
    for (elg_uint32 instance_id = 0; instance_id < MAX_INSTANCES; ++instance_id) {
      WasDestructorCalled[instance_id] = false;
    }
  }

  // Data Members [static]
  static elg_uint32 NextId;
  static bool WasConstructorCalled[MAX_INSTANCES];
  static bool WasDestructorCalled[MAX_INSTANCES];

  // Data Members [static]
  elg_uint32 InstanceId;
};

elg_uint32 TestType::NextId = 0;
bool TestType::WasConstructorCalled[TestType::MAX_INSTANCES];
bool TestType::WasDestructorCalled[TestType::MAX_INSTANCES];

// Tests
TEST(Memory_MallocFree) {
  // Some helper consts
  const elg_size_type AllocationSize = 100;
  const elg_size_type AllocationAlign = 100;

  // Create the allocator
  TestAllocator allocator;

  // Allocate the memory
  void* ptr = ElgMalloc(AllocationSize, AllocationAlign, &allocator);

  // Do the cechking - was the allocation okay
  CHECK_EQUAL(TestAllocator::LAST_CALL_ALLOCATE, allocator.LastCall);
  CHECK_EQUAL(AllocationSize, allocator.Size);
  CHECK_EQUAL(AllocationAlign, allocator.Align);

  // Free the memory
  ElgFree(ptr, &allocator);

    // Do the checking - was the deallocation okay
  CHECK_EQUAL(TestAllocator::LAST_CALL_FREE, allocator.LastCall);
  CHECK_EQUAL(ptr, allocator.Pointer);
}

TEST(Memory_Malloc_OutOfMemory) {
  // Some helper consts
  const elg_size_type AllocationSize = 100;
  const elg_size_type AllocationAlign = 100;

  // Create the allocator
  TestAllocator allocator(true);

  // Allocate the memory
  void* ptr = ElgMalloc(AllocationSize, AllocationAlign, &allocator);

  // Do the cechking - there was a proper call to allocate
  CHECK_EQUAL(TestAllocator::LAST_CALL_ALLOCATE, allocator.LastCall);
  CHECK_EQUAL(AllocationSize, allocator.Size);
  CHECK_EQUAL(AllocationAlign, allocator.Align);

  // Do the cechking - null was returned
  CHECK_EQUAL(static_cast<void*>(NULL), ptr);
}

TEST(Memory_Free_Null) {
  // Create the allocator
  TestAllocator allocator;

  // Create a NULL pointer to a non-POD type
  void* ptr = NULL;

  // Delete
  ElgFree(ptr, &allocator);
}

TEST(Memory_NewDelete) {
  // Create the allocator
  TestAllocator allocator;

  // Reset the class instance information
  TestType::ClearInstanceStates();

  // Test the creation
  elg_uint32 next_instance_id = TestType::NextId;
  TestType* instance = ElgNew(TestType, &allocator);

  // Do the cechking - did we create a right object
  CHECK_EQUAL(next_instance_id, instance->InstanceId);

  // Do the cechking - was the allocation okay
  CHECK_EQUAL(TestAllocator::LAST_CALL_ALLOCATE, allocator.LastCall);
  CHECK(sizeof(TestType) <= allocator.Size);
  CHECK(ELG_ALIGNOF(TestType) <= allocator.Align);

  // Do the cechking - was the constructor called
  CHECK_EQUAL(true, TestType::WasConstructorCalled[next_instance_id]);

  // Test the destruction
  ElgDelete(instance, &allocator);

  // Do the checking - was the deallocation okay
  CHECK_EQUAL(TestAllocator::LAST_CALL_FREE, allocator.LastCall);
  CHECK_EQUAL(instance, allocator.Pointer);

  // Do the cechking - was the destructor called
  CHECK_EQUAL(true, TestType::WasDestructorCalled[next_instance_id]);
}

TEST(Memory_New_OutOfMemory) {
  // Create the allocator that simulates the out of memory conditions
  TestAllocator allocator(true);

  // Reset the class instance information
  TestType::ClearInstanceStates();

  // Test the creation
  elg_uint32 next_instance_id = TestType::NextId;
  TestType* instance = ElgNew(TestType, &allocator);

  // Do the cechking - the next instance id did not change
  CHECK_EQUAL(next_instance_id, TestType::NextId);

  // Do the cechking - there was a proper call to allocate
  CHECK_EQUAL(TestAllocator::LAST_CALL_ALLOCATE, allocator.LastCall);
  CHECK(sizeof(TestType) <= allocator.Size);
  CHECK(ELG_ALIGNOF(TestType) <= allocator.Align);

  // Do the cechking - null was returned
  CHECK_EQUAL(static_cast<TestType*>(NULL), instance);
}

TEST(Memory_Delete_Null) {
  // Create the allocator
  TestAllocator allocator;

  // Create a NULL pointer to a non-POD type
  TestType* non_pod_ptr = NULL;

  // Delete
  ElgDelete(non_pod_ptr, &allocator);

  // Create a NULL pointer to a POD type
  int* pod_ptr = NULL;

  // Delete
  ElgDelete(pod_ptr, &allocator);
}

TEST(Memory_NewArrayDeleteArray) {
  // Some helpful consts
  const elg_uint32 ArrayElements = 10;

  // Create the allocator
  TestAllocator allocator;

  // Reset the class instance information
  TestType::ClearInstanceStates();

  // Test the creation
  elg_uint32 next_instance_id = TestType::NextId;
  TestType* array_ptr = ElgNewArray(TestType, ArrayElements, &allocator);

  // Do the cechking - did we create a right objects
  for (elg_uint32 index = 0;index < ArrayElements; ++index) {
    CHECK_EQUAL(next_instance_id + index, array_ptr[index].InstanceId);
  }

  // Do the cechking - was the allocation okay
  CHECK_EQUAL(TestAllocator::LAST_CALL_ALLOCATE, allocator.LastCall);
  CHECK(ArrayElements * sizeof(TestType) <= allocator.Size);
  CHECK(ELG_ALIGNOF(TestType) <= allocator.Align);

  // Do the cechking - was the constructor called
  for (elg_uint32 index = 0;index < ArrayElements; ++index) {
    CHECK_EQUAL(true, TestType::WasConstructorCalled[next_instance_id + index]);
  }

  // Test the destruction
  ElgDeleteArray(array_ptr, &allocator);

  // Do the checking - was the deallocation okay (we can't really check the pointer since is can be offset by sth.)
  CHECK_EQUAL(TestAllocator::LAST_CALL_FREE, allocator.LastCall);

  // Do the cechking - was the destructor called
  for (elg_uint32 index = 0;index < ArrayElements; ++index) {
    CHECK_EQUAL(true, TestType::WasDestructorCalled[next_instance_id + index]);
  }
}

TEST(Memory_NewArray_OutOfMemory) {
  // Some helpful consts
  const elg_uint32 ArrayElements = 10;

  // Create the allocator that simulates the out of memory conditions
  TestAllocator allocator(true);

  // Reset the class instance information
  TestType::ClearInstanceStates();

  // Test the creation
  elg_uint32 next_instance_id = TestType::NextId;
  TestType* instance = ElgNewArray(TestType, ArrayElements, &allocator);

  // Do the cechking - the next instance id did not change
  CHECK_EQUAL(next_instance_id, TestType::NextId);

  // Do the cechking - there was a proper call to allocate
  CHECK_EQUAL(TestAllocator::LAST_CALL_ALLOCATE, allocator.LastCall);
  CHECK(ArrayElements * sizeof(TestType) <= allocator.Size);
  CHECK(ELG_ALIGNOF(TestType) <= allocator.Align);

  // Do the cechking - null was returned
  CHECK_EQUAL(static_cast<TestType*>(NULL), instance);
}

TEST(Memory_DeleteArray_Null) {
  // Create the allocator
  TestAllocator allocator;

  // Create a NULL pointer to a non-POD type
  TestType* non_pod_ptr = NULL;

  // Delete
  ElgDeleteArray(non_pod_ptr, &allocator);

  // Create a NULL pointer to a POD type
  int* pod_ptr = NULL;

  // Delete
  ElgDeleteArray(pod_ptr, &allocator);
}
