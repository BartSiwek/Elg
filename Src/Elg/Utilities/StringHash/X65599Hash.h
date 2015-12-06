/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_STRINGHASH_X65599HASH_H_
#define ELG_UTILITIES_STRINGHASH_X65599HASH_H_

#include <cstring>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

namespace Elg {
namespace Utilities {
namespace StringHash {

ELG_FORCEINLINE elg_uint32 X65599Hash(const char* s) {
  const elg_size_type length = std::strlen(s) + 1;
  elg_uint32 hash = 0;

  for (elg_size_type index = 0; index < length; ++index) {
    hash = 65599 * hash + s[index];
  }

  return hash ^ (hash >> 16);
}

}  // namespace StringHash
}  // namespace Utilities
}  // namespace Elg

#endif  // ELG_UTILITIES_STRINGHASH_X65599HASH_H_
