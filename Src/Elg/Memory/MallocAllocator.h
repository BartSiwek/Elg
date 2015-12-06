/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_MEMORY_MALLOCALLOCATOR_H_
#define ELG_MEMORY_MALLOCALLOCATOR_H_

#include "Elg/Utilities/Types.h"

namespace Elg {
namespace Memory {
namespace Allocators {

class MallocAllocator {
 public:
  void* Allocate(elg_size_type size, elg_size_type align, const char* file, elg_uint32 line);
  void  Free(void* ptr, const char* file, elg_uint32 line);
};

}  // namespace Allocators
}  // namespace Memory
}  // namespace Elg

#endif  // ELG_MEMORY_MALLOCALLOCATOR_H_
