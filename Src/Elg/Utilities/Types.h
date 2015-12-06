/*
 * Copyright (c) 2011 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_TYPES_H_
#define ELG_UTILITIES_TYPES_H_

#include <cstdint>
#include <cstddef>

#include "Elg/Utilities/Assert/StaticAssert.h"

// Helper classes
namespace Elg {
namespace Utilities {
namespace Types {

template<int SizeOfSystemSizeTypeInBytes>
struct SizeTypeSelector;

template<>
struct SizeTypeSelector<1> {
  typedef std::uint8_t unsigned_size_type;
  typedef std::int8_t signed_size_type;
};

template<>
struct SizeTypeSelector<2> {
  typedef std::uint16_t unsigned_size_type;
  typedef std::int16_t signed_size_type;
};

template<>
struct SizeTypeSelector<4> {
  typedef std::uint32_t unsigned_size_type;
  typedef std::int32_t signed_size_type;
};

template<>
struct SizeTypeSelector<8> {
  typedef std::uint64_t unsigned_size_type;
  typedef std::int64_t signed_size_type;
};

}  // namespace Types
}  // namespace Utilities
}  // namespace Elg

// Define types + make compile time checks
typedef std::uint8_t elg_uint8;
STATIC_ASSERT(sizeof(elg_uint8) == 1, "elg_uint8 is not 8bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::uint16_t elg_uint16;
STATIC_ASSERT(sizeof(elg_uint16) == 2, "elg_uint16 is not 16bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::uint32_t elg_uint32;
STATIC_ASSERT(sizeof(elg_uint32) == 4, "elg_uint32 is not 32bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::uint64_t elg_uint64;
STATIC_ASSERT(sizeof(elg_uint64) == 8, "elg_uint64 is not 64bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::int8_t elg_int8;
STATIC_ASSERT(sizeof(elg_int8) == 1, "elg_int8 is not 8bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::int16_t elg_int16;
STATIC_ASSERT(sizeof(elg_int16) == 2, "elg_int16 is not 16bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::int32_t elg_int32;
STATIC_ASSERT(sizeof(elg_int32) == 4, "elg_int32 is not 32bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::int64_t elg_int64;
STATIC_ASSERT(sizeof(elg_int64) == 8, "elg_int64 is not 64bits long on this system");  // NOLINT(runtime/sizeof)

typedef float elg_float32;
STATIC_ASSERT(sizeof(elg_float32) == 4, "elg_float32 is not 32bits long on this system");  // NOLINT(runtime/sizeof)

typedef double elg_float64;
STATIC_ASSERT(sizeof(elg_float64) == 8, "elg_float64 is not 64bits long on this system");  // NOLINT(runtime/sizeof)

typedef char elg_char;
STATIC_ASSERT(sizeof(elg_char) == 1, "elg_char is not 8bits long on this system");  // NOLINT(runtime/sizeof)

typedef signed char elg_schar;
STATIC_ASSERT(sizeof(elg_schar) == 1, "elg_schar is not 8bits long on this system");  // NOLINT(runtime/sizeof)

typedef unsigned char elg_uchar;
STATIC_ASSERT(sizeof(elg_uchar) == 1, "elg_uchar is not 8bits long on this system");  // NOLINT(runtime/sizeof)

typedef std::uintptr_t elg_uint_pointer;

typedef std::intptr_t elg_int_pointer;

typedef Elg::Utilities::Types::SizeTypeSelector<sizeof(std::size_t)>::unsigned_size_type elg_size_type;

typedef Elg::Utilities::Types::SizeTypeSelector<sizeof(std::size_t)>::signed_size_type elg_signed_size_type;

typedef ptrdiff_t elg_pointer_diff;

#endif  // ELG_UTILITIES_TYPES_H_
