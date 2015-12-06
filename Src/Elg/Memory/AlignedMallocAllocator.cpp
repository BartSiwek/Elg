/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include "Elg/Memory/AlignedMallocAllocator.h"

#include <cstdlib>

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace Memory {
namespace Allocators {


void* AlignedMallocAllocator::Allocate(elg_size_type size, elg_size_type align, const char* /* file */,
                                       elg_uint32 /* line */) {
  return _aligned_malloc(size, align);
}

void  AlignedMallocAllocator::Free(void* ptr, const char* /* file */, elg_uint32 /* line */) {
  _aligned_free(ptr);
}


}  // namespace Allocators
}  // namespace Memory
}  // namespace Elg
