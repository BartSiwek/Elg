/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_STRINGHASH_HASH_H_
#define ELG_UTILITIES_STRINGHASH_HASH_H_

#include <string>

#include "Elg/Utilities/Preprocessor/repeat.hpp"
#include "Elg/Utilities/Preprocessor/arithmetic.hpp"

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/StringHash/X65599Hash.h"
#include "Elg/Utilities/StringHash/X65599HashPreprocessor.h"

namespace Elg {
namespace Utilities {
namespace StringHash {

// For VS use /O2 or /Ox with tip below:
//   String Pooling option is off for /Ox by default while it is on for both /O1 and /O2
//   Enable C/C++ > Code Generation > Enable String Polling for the string to disappear
// For GCC use -O3
// For other try and look at disassembly/search binary for text to see if it works...

// Regular hash function
struct ConstCharWrapper {
  ELG_FORCEINLINE ConstCharWrapper(const char* s) : String(s) {
  }

  ELG_FORCEINLINE ConstCharWrapper(const std::string s) : String(s.c_str()) {
  }

  const char* String;
};

ELG_FORCEINLINE elg_uint32 Hash(ConstCharWrapper wrapper) {
  return X65599Hash(wrapper.String);
}

// Preprocessor generated hash function (with helper macro)
#define ELG_STRING_HASH_FUNCTION(Z, N, DATA)                                                                          \
  ELG_FORCEINLINE elg_uint32 Hash(const char (&s)[BOOST_PP_ADD(N, 1)]) {                                              \
    return ELG_X65599(s, BOOST_PP_ADD(N, 1));                                                                         \
  }
BOOST_PP_REPEAT(128, ELG_STRING_HASH_FUNCTION, DONT_CARE)
#undef ELG_STRING_HASH_FUNCTION

}  // namespace StringHash
}  // namespace Utilities
}  // namespace Elg

// Helper macro for hashing strings
#define ELG_STRING_HASH(STRING_TO_HASH) Elg::Utilities::StringHash::Hash(STRING_TO_HASH)

#endif  // ELG_UTILITIES_STRINGHASH_HASH_H_
