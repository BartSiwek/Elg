/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 * Based on EASTL (https://github.com/paulhodge/EASTL) - copyright information follows.
 */

/*
 * Copyright (C) 2005,2009-2010 Electronic Arts, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Electronic Arts, Inc. ("EA") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY ELECTRONIC ARTS AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ELECTRONIC ARTS OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ELG_UTILITIES_ETL_TYPETRAITS_H_
#define ELG_UTILITIES_ETL_TYPETRAITS_H_

#include <type_traits>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

namespace Elg {
namespace Utilities {
namespace Etl {

// Import the things from std
using std::integral_constant;
using std::true_type;
using std::false_type;

// yes_type / no_type
//   These are used as a utility to differentiate between two things.
typedef char yes_type;                          // sizeof(yes_type) == 1
struct       no_type {                          // sizeof(no_type)  != 1
  elg_int8 padding[8];
};

// type_select
//   This is used to declare a type from one of two type options. The result is based on the condition type. This has
//   certain uses in template metaprogramming.
//
//   Example usage:
//     typedef ChosenType = type_select<is_integral<SomeType>::value, ChoiceAType, ChoiceBType>::type;
template<bool Condition, typename ConditionIsTrueType, typename ConditionIsFalseType>
struct type_select;

template<typename ConditionIsTrueType, typename ConditionIsFalseType>
struct type_select<true, ConditionIsTrueType, ConditionIsFalseType> {
  typedef ConditionIsTrueType type;
};

template<typename ConditionIsTrueType, typename ConditionIsFalseType>
struct type_select<false, ConditionIsTrueType, ConditionIsFalseType> {
  typedef ConditionIsFalseType type;
};

// type_or
//   This is a utility class for creating composite type traits.
template<bool b1, bool b2, bool b3 = false, bool b4 = false, bool b5 = false>
struct type_or;

template<bool b1, bool b2, bool b3, bool b4, bool b5>
struct type_or {
  static const bool value = true;
};

template<>
struct type_or<false, false, false, false, false> {
  static const bool value = false;
};

// type_and
//   This is a utility class for creating composite type traits.
template<bool b1, bool b2, bool b3 = true, bool b4 = true, bool b5 = true>
struct type_and;

template<bool b1, bool b2, bool b3, bool b4, bool b5>
struct type_and {
  static const bool value = false;
};

template<>
struct type_and<true, true, true, true, true> {
  static const bool value = true;
};

// type_equal
//   This is a utility class for creating composite type traits.
template<elg_int32 b1, elg_int32 b2>
struct type_equal {
  static const bool value = (b1 == b2);
};

// type_not_equal
//   This is a utility class for creating composite type traits.
template<elg_int32 b1, elg_int32 b2>
struct type_not_equal {
  static const bool value = (b1 != b2);
};

// type_not
//   This is a utility class for creating composite type traits.
template<bool b>
struct type_not;

template<>
struct type_not<true> {
  static const bool value = false;
};

template<>
struct type_not<false> {
  static const bool value = true;
};

// empty
template<typename T>
struct empty {
};

// Import the things from std - fundamental type queries
using std::is_void;
using std::is_integral;
using std::is_floating_point;
using std::is_arithmetic;
using std::is_fundamental;

// Type transformations
// add_signed
//   Adds signed-ness to the given type. Modifies only integral values; has no effect on others.
//   add_signed<int>::type is int
//   add_signed<unsigned int>::type is int
template<class T>
struct add_signed {
  typedef T type;
};

template<>
struct add_signed<elg_uint8> {
  typedef elg_int8 type;
};

template<>
struct add_signed<elg_uint16> {
  typedef elg_int16 type;
};

template<>
struct add_signed<elg_uint32> {
  typedef elg_int32 type;
};

template<>
struct add_signed<elg_uint64> {
  typedef elg_int64 type;
};

// add_unsigned
//   Adds unsigned-ness to the given type. Modifies only integral values; has no effect on others.
//     add_unsigned<int>::type is unsigned int
//     add_unsigned<unsigned int>::type is unsigned int
template<class T>
struct add_unsigned {
  typedef T type;
};

template<>
struct add_unsigned<elg_int8> {
  typedef elg_uint8 type;
};

template<>
struct add_unsigned<elg_int16> {
  typedef elg_uint16 type;
};

template<>
struct add_unsigned<elg_int32> {
  typedef elg_uint32 type;
};

template<>
struct add_unsigned<elg_int64> {
  typedef elg_uint64 type;
};

// Import from std
using std::remove_cv;
using std::add_reference;

// Type properties
using std::is_const;
using std::is_volatile;
using std::is_abstract;
using std::is_signed;
using std::is_unsigned;
using std::rank;
using std::extent;
using std::is_base_of;

#define ETL_DECLARE_SIGNED(T)                                                                                         \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct is_signed<T> : public true_type {                                                                              \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct is_signed<const T> : public true_type {                                                                        \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

#define ETL_DECLARE_UNSIGNED(T)                                                                                       \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct is_unsigned<T> : public true_type {                                                                            \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct is_unsigned<const T> : public true_type {                                                                      \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

// alignment_of
//   alignment_of<T>::value is an integral value representing, in bytes, the memory alignment of objects of type T.
//
//   alignment_of may only be applied to complete types.
template<typename T>
struct alignment_of_value {
  static const elg_size_type value = ELG_ALIGNOF(T);
};

template<typename T>
struct alignment_of : public Elg::Utilities::Etl::integral_constant<elg_size_type, alignment_of_value<T>::value> {
};

// is_aligned
//   Defined as true if the type has alignment requirements greater than default alignment, which is taken to be 8.
//   This allows for doing specialized object allocation and placement for such types.
template<typename T>
struct is_aligned_value {
  static const bool value = (ELG_ALIGNOF(T) > 8);
};

template<typename T>
struct is_aligned : public integral_constant<bool, is_aligned_value<T>::value> {
};

// Compound types
using std::is_array;
using std::is_reference;
using std::is_member_function_pointer;
using std::is_member_pointer;
using std::is_pointer;
using std::is_same;
using std::is_convertible;
using std::is_union;
using std::is_class;
using std::is_enum;
using std::is_polymorphic;
using std::is_function;
using std::is_object;
using std::is_scalar;
using std::is_compound;

#define ETL_DECLARE_UNION(T)                                                                                          \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct is_union<T> : public true_type {                                                                               \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct is_union<const T> : public true_type {                                                                         \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

#define ETL_DECLARE_ENUM(T)                                                                                           \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct is_enum<T> : public true_type {                                                                                \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct is_enum<const T> : public true_type {                                                                          \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

// Pod types
using std::is_empty;
using std::is_pod;
using std::has_trivial_constructor;
using std::has_trivial_copy;
using std::has_trivial_assign;
using std::has_trivial_destructor;

// With current compilers, this is all we can do.
template<typename T>
struct has_trivial_relocate : public integral_constant<bool, is_pod<T>::value && !is_volatile<T>::value> {
};

#define ETL_DECLARE_POD(T)                                                                                            \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct is_pod<T> : public true_type {                                                                                 \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct is_pod<const T> : public true_type {                                                                           \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

#define ETL_DECLARE_TRIVIAL_CONSTRUCTOR(T)                                                                            \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_constructor<T> : public true_type {                                                                \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_constructor<const T> : public true_type {                                                          \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

#define ETL_DECLARE_TRIVIAL_COPY(T)                                                                                   \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_copy<T> : public true_type {                                                                       \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_copy<const T> : public true_type {                                                                 \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

#define ETL_DECLARE_TRIVIAL_ASSIGN(T)                                                                                 \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_assign<T> : public true_type {                                                                     \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_assign<const T> : public true_type {                                                               \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

#define ETL_DECLARE_TRIVIAL_DESTRUCTOR(T)                                                                             \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_destructor<T> : public true_type {                                                                 \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_destructor<const T> : public true_type {                                                           \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

#define ETL_DECLARE_TRIVIAL_RELOCATE(T)                                                                               \
namespace Elg {                                                                                                       \
namespace Utilities {                                                                                                 \
namespace Etl {                                                                                                       \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_relocate<T> : public true_type {                                                                   \
};                                                                                                                    \
                                                                                                                      \
template<>                                                                                                            \
struct has_trivial_relocate<const T> : public true_type {                                                             \
};                                                                                                                    \
                                                                                                                      \
}                                                                                                                     \
}                                                                                                                     \
}

}  // namespace Etl
}  // namespace Utilities
}  // namespace Elg

#endif  // ELG_UTILITIES_ETL_TYPETRAITS_H_
