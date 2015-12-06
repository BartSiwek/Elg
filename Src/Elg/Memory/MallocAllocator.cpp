/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include "Elg/Memory/MallocAllocator.h"

#include <cstdlib>

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace Memory {
namespace Allocators {

void* MallocAllocator::Allocate(elg_size_type size, elg_size_type /* align */, const char* /* file */,
                                elg_uint32 /* line */) {
  return std::malloc(size);
}

void MallocAllocator::Free(void* ptr, const char* /* file */, elg_uint32 /* line */) {
  std::free(ptr);
}

}  // namespace Allocators
}  // namespace Memory
}  // namespace Elg
