/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#include <cstdlib>
#include <new>

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"

void* operator new[] (elg_size_type size) {
  ASSERT(false, "Use of default new/delete is forbidden. Use Elg::Memory members");
  return std::malloc(size);
}

void* operator new[] (elg_size_type size, const std::nothrow_t& /* nt */) throw() {
  ASSERT(false, "Use of default new/delete is forbidden. Use Elg::Memory members");
  return std::malloc(size);
}

void operator delete[] (void* ptr) {
  ASSERT(false, "Use of default new/delete is forbidden. Use Elg::Memory members");
  std::free(ptr);
}

void operator delete[] (void* ptr, const std::nothrow_t& /* nt */) throw() {
  ASSERT(false, "Use of default new/delete is forbidden. Use Elg::Memory members");
  std::free(ptr);
}
