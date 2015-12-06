/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/ETL/Utility.h"

#include "Elg/Utilities/ETL/GenericIterator.h"

TEST(Etl_GenericIterator_Construction) {
  // Test default construction
  Elg::Utilities::Etl::generic_iterator<elg_int32*> default_constructed;
  CHECK(static_cast<elg_int32*>(NULL) == &*default_constructed);

  // Test construction for base iterator type
  elg_int32 value = 123;
  Elg::Utilities::Etl::generic_iterator<elg_int32*> iterator32_constructed(&value);
  CHECK(&value == &*iterator32_constructed);

  // Test construction from other generic_iterator
  Elg::Utilities::Etl::generic_iterator<elg_int32*> copy_constructed(iterator32_constructed);
  CHECK(&value == &*copy_constructed);

  // Test construction from other generic_iterator with different underlying type
  Elg::Utilities::Etl::generic_iterator<const elg_int32*> other_constructed(iterator32_constructed);
  CHECK(&value == &*other_constructed);
}

TEST(Etl_GenericIterator_Operations) {
  // Helper vars
  elg_int32 test_value = 123;
  elg_int32 test_array[] = {1, 2, 3};
  Elg::Utilities::Etl::pair<elg_int32, elg_uint16> test_pair(-1, 2);

  // Test - operator= and operator*
  Elg::Utilities::Etl::generic_iterator<elg_int32*> value_iterator;
  value_iterator = &test_value;
  CHECK(&test_value == &*value_iterator);

  // Test - base function
  CHECK(&test_value == value_iterator.base());

  // Test - operator->
  typedef Elg::Utilities::Etl::pair<elg_int32, elg_uint16> IteratedType;  // NOLINT(build/include_what_you_use)
  Elg::Utilities::Etl::generic_iterator<IteratedType*> pair_iterator(&test_pair);
  CHECK(test_pair.first == pair_iterator->first);
  CHECK(test_pair.second == pair_iterator->second);

  // Test - operator++ prefix
  Elg::Utilities::Etl::generic_iterator<elg_int32*> array_iterator(test_array);
  CHECK(test_array == &*array_iterator);
  ++array_iterator;
  CHECK((test_array + 1) == &*array_iterator);

  // Test - operator-- prefix
  --array_iterator;
  CHECK(test_array == &*array_iterator);

  // Test - operator++ postfix
  Elg::Utilities::Etl::generic_iterator<elg_int32*> postfix_add_iterator = array_iterator++;
  CHECK(test_array == &*postfix_add_iterator);
  CHECK((test_array + 1) == &*array_iterator);

  // Test - operator-- postfix
  Elg::Utilities::Etl::generic_iterator<elg_int32*> postfix_sub_iterator = array_iterator--;
  CHECK((test_array + 1) == &*postfix_sub_iterator);
  CHECK(test_array == &*array_iterator);

  // Test - operator[]
  CHECK(test_array + 2 == &array_iterator[2]);

  // Test - operator+=
  array_iterator += 2;
  CHECK(test_array + 2 == &*array_iterator);

  // Test - operator-=
  array_iterator -= 1;
  CHECK(test_array + 1 == &*array_iterator);

  // Test - operator+
  CHECK(test_array + 2 == &*(array_iterator + 1));

  // Test - operator+
  CHECK(test_array + 2 == &*(1 + array_iterator));

  // Test - operator-
  CHECK(test_array == &*(array_iterator - 1));

  // Test - operator- for two iterators
  Elg::Utilities::Etl::generic_iterator<elg_int32*> other_iterator(test_array + 2);
  array_iterator = test_array;
  CHECK_EQUAL(2, other_iterator - array_iterator);
  CHECK_EQUAL(-2, array_iterator - other_iterator);
}

TEST(Etl_GenericIterator_Comparisons) {
  // Helper vars
  elg_int32 test_array[] = {2, 1};

  // Appropriate iterators
  Elg::Utilities::Etl::generic_iterator<const elg_int32*> const_first_element_iterator(test_array);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> first_element_iterator(test_array);

  Elg::Utilities::Etl::generic_iterator<const elg_int32*> const_second_element_iterator(test_array + 1);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> second_element_iterator(test_array + 1);

  // Test comparisons - first smaller then second
  CHECK(!(first_element_iterator == second_element_iterator));
  CHECK(first_element_iterator != second_element_iterator);
  CHECK(first_element_iterator <  second_element_iterator);
  CHECK(first_element_iterator <= second_element_iterator);
  CHECK(!(first_element_iterator >  second_element_iterator));
  CHECK(!(first_element_iterator >= second_element_iterator));

  CHECK(!(const_first_element_iterator == second_element_iterator));
  CHECK(const_first_element_iterator != second_element_iterator);
  CHECK(const_first_element_iterator <  second_element_iterator);
  CHECK(const_first_element_iterator <= second_element_iterator);
  CHECK(!(const_first_element_iterator >  second_element_iterator));
  CHECK(!(const_first_element_iterator >= second_element_iterator));

  CHECK(!(first_element_iterator == const_second_element_iterator));
  CHECK(first_element_iterator != const_second_element_iterator);
  CHECK(first_element_iterator <  const_second_element_iterator);
  CHECK(first_element_iterator <= const_second_element_iterator);
  CHECK(!(first_element_iterator >  const_second_element_iterator));
  CHECK(!(first_element_iterator >= const_second_element_iterator));

  // Test comparisons - both equal
  CHECK(first_element_iterator == first_element_iterator);
  CHECK(!(first_element_iterator != first_element_iterator));
  CHECK(!(first_element_iterator <  first_element_iterator));
  CHECK(first_element_iterator <= first_element_iterator);
  CHECK(!(first_element_iterator >  first_element_iterator));
  CHECK(first_element_iterator >= first_element_iterator);

  CHECK(const_first_element_iterator == first_element_iterator);
  CHECK(!(const_first_element_iterator != first_element_iterator));
  CHECK(!(const_first_element_iterator <  first_element_iterator));
  CHECK(const_first_element_iterator <= first_element_iterator);
  CHECK(!(const_first_element_iterator >  first_element_iterator));
  CHECK(const_first_element_iterator >= first_element_iterator);

  CHECK(first_element_iterator == const_first_element_iterator);
  CHECK(!(first_element_iterator != const_first_element_iterator));
  CHECK(!(first_element_iterator <  const_first_element_iterator));
  CHECK(first_element_iterator <= const_first_element_iterator);
  CHECK(!(first_element_iterator >  const_first_element_iterator));
  CHECK(first_element_iterator >= const_first_element_iterator);

  // Test comparisons - first greater then the second
  CHECK(!(second_element_iterator == first_element_iterator));
  CHECK(second_element_iterator != first_element_iterator);
  CHECK(!(second_element_iterator <  first_element_iterator));
  CHECK(!(second_element_iterator <= first_element_iterator));
  CHECK(second_element_iterator >  first_element_iterator);
  CHECK(second_element_iterator >= first_element_iterator);

  CHECK(!(const_second_element_iterator == first_element_iterator));
  CHECK(const_second_element_iterator != first_element_iterator);
  CHECK(!(const_second_element_iterator <  first_element_iterator));
  CHECK(!(const_second_element_iterator <= first_element_iterator));
  CHECK(const_second_element_iterator >  first_element_iterator);
  CHECK(const_second_element_iterator >= first_element_iterator);

  CHECK(!(second_element_iterator == const_first_element_iterator));
  CHECK(second_element_iterator != const_first_element_iterator);
  CHECK(!(second_element_iterator <  const_first_element_iterator));
  CHECK(!(second_element_iterator <= const_first_element_iterator));
  CHECK(second_element_iterator >  const_first_element_iterator);
  CHECK(second_element_iterator >= const_first_element_iterator);
}
