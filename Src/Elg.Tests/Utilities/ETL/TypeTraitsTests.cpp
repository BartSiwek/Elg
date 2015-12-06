/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

#include "Elg/Utilities/ETL/TypeTraits.h"

// The following traits are not tested as currently they are imported from std
//   is_void
//   is_integral
//   is_floating_point
//   is_arithmetic
//   is_fundamental
//   remove_cv
//   add_reference
//   is_const
//   is_volatile
//   is_abstract
//   is_signed
//   is_unsigned
//   rank
//   extent
//   is_base_of
//   is_array
//   is_reference
//   is_member_function_pointer
//   is_member_pointer
//   is_pointer
//   is_same
//   is_convertible
//   is_union
//   is_class
//   is_enum
//   is_polymorphic
//   is_function
//   is_object
//   is_scalar
//   is_compound
//   is_empty
//   is_pod
//   has_trivial_constructor
//   has_trivial_copy
//   has_trivial_assign
//   has_trivial_destructor

// Helpers
struct C {
};

struct D {
};

// Tests
TEST(Etl_TypeTraits_YesNoType) {
  CHECK_EQUAL(true, sizeof(Elg::Utilities::Etl::yes_type) == 1);
  CHECK_EQUAL(true, sizeof(Elg::Utilities::Etl::no_type) != 1);
}

TEST(Etl_TypeTraits_TypeSelect) {
  const bool Result1 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::type_select<true, C, D>::type, C>::value;
  CHECK_EQUAL(true, Result1);
  const bool Result2 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::type_select<false, C, D>::type, D>::value;
  CHECK_EQUAL(true, Result2);
}

TEST(Etl_TypeTraits_TypeOr) {
  const bool Result1 = Elg::Utilities::Etl::type_or<false, false, false, false, false>::value;
  CHECK_EQUAL(false, Result1);
  const bool Result2 = Elg::Utilities::Etl::type_or<false, false, false, false, true>::value;
  CHECK_EQUAL(true, Result2);
  const bool Result3 = Elg::Utilities::Etl::type_or<false, false, false, true, true>::value;
  CHECK_EQUAL(true, Result3);
  const bool Result4 = Elg::Utilities::Etl::type_or<false, false, true, true, true>::value;
  CHECK_EQUAL(true, Result4);
  const bool Result5 = Elg::Utilities::Etl::type_or<false, true, true, true, true>::value;
  CHECK_EQUAL(true, Result5);
  const bool Result6 = Elg::Utilities::Etl::type_or<true, true, true, true, true>::value;
  CHECK_EQUAL(true, Result6);
}

TEST(Etl_TypeTraits_TypeAnd) {
  const bool Result1 = Elg::Utilities::Etl::type_and<false, false, false, false, false>::value;
  CHECK_EQUAL(false, Result1);
  const bool Result2 = Elg::Utilities::Etl::type_and<false, false, false, false, true>::value;
  CHECK_EQUAL(false, Result2);
  const bool Result3 = Elg::Utilities::Etl::type_and<false, false, false, true, true>::value;
  CHECK_EQUAL(false, Result3);
  const bool Result4 = Elg::Utilities::Etl::type_and<false, false, true, true, true>::value;
  CHECK_EQUAL(false, Result4);
  const bool Result5 = Elg::Utilities::Etl::type_and<false, true, true, true, true>::value;
  CHECK_EQUAL(false, Result5);
  const bool Result6 = Elg::Utilities::Etl::type_and<true, true, true, true, true>::value;
  CHECK_EQUAL(true, Result6);
}

TEST(Etl_TypeTraits_TypeEqual) {
  const bool Result1 = Elg::Utilities::Etl::type_equal<1, 2>::value;
  CHECK_EQUAL(false, Result1);
  const bool Result2 = Elg::Utilities::Etl::type_equal<0, 0>::value;
  CHECK_EQUAL(true, Result2);
}

TEST(Etl_TypeTraits_TypeNotEqual) {
  const bool Result1 = Elg::Utilities::Etl::type_not_equal<1, 2>::value;
  CHECK_EQUAL(true, Result1);
  const bool Result2 = Elg::Utilities::Etl::type_not_equal<0, 0>::value;
  CHECK_EQUAL(false, Result2);
}

TEST(Etl_TypeTraits_TypeNot) {
  const bool Result1 = Elg::Utilities::Etl::type_not<true>::value;
  CHECK_EQUAL(false, Result1);
  const bool Result2 = Elg::Utilities::Etl::type_not<false>::value;
  CHECK_EQUAL(true, Result2);
}

TEST(Etl_TypeTraits_AddSigned) {
  // No change for unknown types
  const bool Result1 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<C>::type, C>::value;
  CHECK_EQUAL(true, Result1);

  // Change for unsigned types
  const bool Result2 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_uint8>::type,
                                                    elg_int8>::value;
  CHECK_EQUAL(true, Result2);
  const bool Result3 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_uint16>::type,
                                                    elg_int16>::value;
  CHECK_EQUAL(true, Result3);
  const bool Result4 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_uint32>::type,
                                                    elg_int32>::value;
  CHECK_EQUAL(true, Result4);
  const bool Result5 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_uint64>::type,
                                                    elg_int64>::value;
  CHECK_EQUAL(true, Result5);

  // No change for signed types
  const bool Result6 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_int8>::type,
                                                    elg_int8>::value;
  CHECK_EQUAL(true, Result6);
  const bool Result7 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_int16>::type,
                                                    elg_int16>::value;
  CHECK_EQUAL(true, Result7);
  const bool Result8 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_int32>::type,
                                                    elg_int32>::value;
  CHECK_EQUAL(true, Result8);
  const bool Result9 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_int64>::type,
                                                     elg_int64>::value;
  CHECK_EQUAL(true, Result9);

  // uintptr_t -> intptr_t (this makes sense in C++11 and, if both types are present, in C99)
  const bool Result10 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_uint_pointer>::type,
    elg_int_pointer>::value;
  CHECK_EQUAL(true, Result10);
  const bool Result11 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_int_pointer>::type,
    elg_int_pointer>::value;
  CHECK_EQUAL(true, Result11);

  // No change for other Elg types
  const bool Result12 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_float32>::type,
    elg_float32>::value;
  CHECK_EQUAL(true, Result12);
  const bool Result13 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_float64>::type,
    elg_float64>::value;
  CHECK_EQUAL(true, Result13);

  // Pointer differences are signed
  const bool Result14 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_pointer_diff>::type,
    elg_pointer_diff>::value;
  CHECK_EQUAL(true, Result14);

  // We got a pair of types here
  const bool Result15 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_size_type>::type,
    elg_signed_size_type>::value;
  CHECK_EQUAL(true, Result15);
  const bool Result16 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_signed<elg_signed_size_type>::type,
    elg_signed_size_type>::value;
  CHECK_EQUAL(true, Result16);
}

TEST(Etl_TypeTraits_AddUnsigned) {
  // No change for unknown types
  const bool Result1 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<C>::type, C>::value;
  CHECK_EQUAL(true, Result1);

  // No change for unsigned types
  const bool Result2 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_uint8>::type,
    elg_uint8>::value;
  CHECK_EQUAL(true, Result2);
  const bool Result3 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_uint16>::type,
    elg_uint16>::value;
  CHECK_EQUAL(true, Result3);
  const bool Result4 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_uint32>::type,
    elg_uint32>::value;
  CHECK_EQUAL(true, Result4);
  const bool Result5 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_uint64>::type,
    elg_uint64>::value;
  CHECK_EQUAL(true, Result5);

  // Change for signed types
  const bool Result6 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_int8>::type,
    elg_uint8>::value;
  CHECK_EQUAL(true, Result6);
  const bool Result7 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_int16>::type,
    elg_uint16>::value;
  CHECK_EQUAL(true, Result7);
  const bool Result8 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_int32>::type,
    elg_uint32>::value;
  CHECK_EQUAL(true, Result8);
  const bool Result9 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_int64>::type,
    elg_uint64>::value;
  CHECK_EQUAL(true, Result9);

  // intptr_t -> uintptr_t (this makes sense in C++11 and, if both types are present, in C99)
  const bool Result10 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_uint_pointer>::type,
    elg_uint_pointer>::value;
  CHECK_EQUAL(true, Result10);
  const bool Result11 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_int_pointer>::type,
    elg_uint_pointer>::value;
  CHECK_EQUAL(true, Result11);

  // No change for other Elg types
  const bool Result12 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_float32>::type,
    elg_float32>::value;
  CHECK_EQUAL(true, Result12);
  const bool Result13 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_float64>::type,
    elg_float64>::value;
  CHECK_EQUAL(true, Result13);

  // For pointer differences size_type looks like the right type to go to when adding unsigned
  const bool Result14 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_pointer_diff>::type,
    elg_size_type>::value;
  CHECK_EQUAL(true, Result14);

  // We got a pair of types here
  const bool Result15 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_size_type>::type,
    elg_size_type>::value;
  CHECK_EQUAL(true, Result15);
  const bool Result16 = Elg::Utilities::Etl::is_same<Elg::Utilities::Etl::add_unsigned<elg_signed_size_type>::type,
    elg_size_type>::value;
  CHECK_EQUAL(true, Result16);
}
