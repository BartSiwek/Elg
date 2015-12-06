/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/ETL/TypeTraits.h"

#include "Elg/Utilities/ETL/Utility.h"

// Helper classes
struct RelOpsEqualityTestHelper {
  explicit RelOpsEqualityTestHelper(elg_int32 x)
      : X(x) {
  }

  bool operator==(const RelOpsEqualityTestHelper& other) const {
    return (X == other.X);
  }

  elg_int32 X;
};

struct RelOpsOrderingTestHelper {
  explicit RelOpsOrderingTestHelper(elg_int32 x)
    : X(x) {
  }

  bool operator<(const RelOpsOrderingTestHelper& other) const {
    return (X < other.X);
  }

  elg_int32 X;
};


// Tests
TEST(Etl_Utility_RelOps) {
  // Get the relops
  using namespace Elg::Utilities::Etl::rel_ops;  // NOLINT(build/namespaces)

  // Equality inequality testing
  RelOpsEqualityTestHelper helper_equal_first(1);
  RelOpsEqualityTestHelper helper_equal_second(1);
  RelOpsEqualityTestHelper helper_equal_third(-1);

  CHECK_EQUAL(true,  helper_equal_first == helper_equal_second);
  CHECK_EQUAL(false, helper_equal_first != helper_equal_second);

  CHECK_EQUAL(false, helper_equal_first == helper_equal_third);
  CHECK_EQUAL(true,  helper_equal_first != helper_equal_third);

  // Ordering testing
  RelOpsOrderingTestHelper helper_equal_one(1);
  RelOpsOrderingTestHelper helper_equal_three(3);

  CHECK_EQUAL(false, helper_equal_one < helper_equal_one);
  CHECK_EQUAL(true,  helper_equal_one < helper_equal_three);
  CHECK_EQUAL(false, helper_equal_three < helper_equal_one);

  CHECK_EQUAL(true,  helper_equal_one <= helper_equal_one);
  CHECK_EQUAL(true,  helper_equal_one <= helper_equal_three);
  CHECK_EQUAL(false, helper_equal_three <= helper_equal_one);

  CHECK_EQUAL(false, helper_equal_one > helper_equal_one);
  CHECK_EQUAL(false, helper_equal_one > helper_equal_three);
  CHECK_EQUAL(true,  helper_equal_three > helper_equal_one);

  CHECK_EQUAL(true,  helper_equal_one >= helper_equal_one);
  CHECK_EQUAL(false, helper_equal_one >= helper_equal_three);
  CHECK_EQUAL(true,  helper_equal_three >= helper_equal_one);
}

TEST(Etl_Utility_Pair_Construction) {
  Elg::Utilities::Etl::pair<elg_int32, elg_int32> default_constructed;

  CHECK_EQUAL(0, default_constructed.first);
  CHECK_EQUAL(0, default_constructed.second);

  Elg::Utilities::Etl::pair<elg_int32, elg_int32> two_argument_constructed(1, 2);

  CHECK_EQUAL(1, two_argument_constructed.first);
  CHECK_EQUAL(2, two_argument_constructed.second);

  Elg::Utilities::Etl::pair<elg_uint16, elg_uint16> uint_constructed(1, 5);
  Elg::Utilities::Etl::pair<elg_int32, elg_int32> copy_constructed(uint_constructed);

  CHECK_EQUAL(1, copy_constructed.first);
  CHECK_EQUAL(5, copy_constructed.second);
}

TEST(Etl_Utility_Pair_RelOps_Equality) {
  RelOpsEqualityTestHelper one_value(1);
  RelOpsEqualityTestHelper three_value(3);

  Elg::Utilities::Etl::pair<RelOpsEqualityTestHelper, RelOpsEqualityTestHelper> first_pair(one_value, one_value);
  Elg::Utilities::Etl::pair<RelOpsEqualityTestHelper, RelOpsEqualityTestHelper> second_pair(one_value, one_value);
  Elg::Utilities::Etl::pair<RelOpsEqualityTestHelper, RelOpsEqualityTestHelper> third_pair(one_value, three_value);
  Elg::Utilities::Etl::pair<RelOpsEqualityTestHelper, RelOpsEqualityTestHelper> fourth_pair(three_value, one_value);
  Elg::Utilities::Etl::pair<RelOpsEqualityTestHelper, RelOpsEqualityTestHelper> fifth_pair(three_value, three_value);

  CHECK_EQUAL(true, first_pair == second_pair);
  CHECK_EQUAL(false, first_pair == third_pair);
  CHECK_EQUAL(false, first_pair == fourth_pair);
  CHECK_EQUAL(false, first_pair == fifth_pair);

  CHECK_EQUAL(false, first_pair != second_pair);
  CHECK_EQUAL(true, first_pair != third_pair);
  CHECK_EQUAL(true, first_pair != fourth_pair);
  CHECK_EQUAL(true, first_pair != fifth_pair);
}

TEST(Etl_Utility_Pair_RelOps_Ordering) {
  RelOpsOrderingTestHelper one_value(1);
  RelOpsOrderingTestHelper three_value(3);

  Elg::Utilities::Etl::pair<RelOpsOrderingTestHelper, RelOpsOrderingTestHelper> one_one_pair(one_value, one_value);
  Elg::Utilities::Etl::pair<RelOpsOrderingTestHelper, RelOpsOrderingTestHelper> one_three_pair(one_value, three_value);
  Elg::Utilities::Etl::pair<RelOpsOrderingTestHelper, RelOpsOrderingTestHelper> three_one_pair(three_value, one_value);

  CHECK_EQUAL(false, one_one_pair < one_one_pair);
  CHECK_EQUAL(true, one_one_pair < one_three_pair);
  CHECK_EQUAL(false, three_one_pair < one_one_pair);

  CHECK_EQUAL(true, one_one_pair <= one_one_pair);
  CHECK_EQUAL(true, one_one_pair <= one_three_pair);
  CHECK_EQUAL(false, three_one_pair <= one_one_pair);

  CHECK_EQUAL(false, one_one_pair > one_one_pair);
  CHECK_EQUAL(false, one_one_pair > one_three_pair);
  CHECK_EQUAL(true, three_one_pair > one_one_pair);

  CHECK_EQUAL(true, one_one_pair >= one_one_pair);
  CHECK_EQUAL(false, one_one_pair >= one_three_pair);
  CHECK_EQUAL(true, three_one_pair >= one_one_pair);
}

TEST(Etl_Utility_UseSelf) {
  // Helper typedefs
  typedef Elg::Utilities::Etl::pair<elg_int32, elg_float32> TestType;

  // Check the result type
  const bool ok_result_type =
    Elg::Utilities::Etl::is_same<TestType, Elg::Utilities::Etl::use_self<TestType>::result_type>::value;
  CHECK(ok_result_type);

  // Check the () operator
  Elg::Utilities::Etl::use_self<TestType> use_self_instance;
  TestType test_type_intance(-12, 1.0);
  CHECK(test_type_intance == use_self_instance(test_type_intance));
}

TEST(Etl_Utility_UseFirst) {
  // Helper typedefs
  typedef Elg::Utilities::Etl::pair<elg_int32, elg_float32> TestType;

  // Check the result type
  const bool ok_result_type =
    Elg::Utilities::Etl::is_same<elg_int32, Elg::Utilities::Etl::use_first<TestType>::result_type>::value;
  CHECK(ok_result_type);

  // Check the () operator
  Elg::Utilities::Etl::use_first<TestType> use_first_instance;
  TestType test_type_intance(-12, 1.0);
  CHECK_EQUAL(-12, use_first_instance(test_type_intance));
}

TEST(Etl_Utility_UseSecond) {
  // Helper typedefs
  typedef Elg::Utilities::Etl::pair<elg_int32, elg_float32> TestType;

  // Check the result type
  const bool ok_result_type =
    Elg::Utilities::Etl::is_same<elg_float32, Elg::Utilities::Etl::use_second<TestType>::result_type>::value;
  CHECK(ok_result_type);

  // Check the () operator
  Elg::Utilities::Etl::use_second<TestType> use_second_instance;
  TestType test_type_intance(-12, 1.0);
  CHECK_EQUAL(1.0, use_second_instance(test_type_intance));
}

TEST(Etl_Utility_MakePair) {
  Elg::Utilities::Etl::pair<elg_int32, elg_float32> p = Elg::Utilities::Etl::make_pair(-2, 1.0f);

  CHECK_EQUAL(-2, p.first);
  CHECK_EQUAL(1.0, p.second);

  typedef Elg::Utilities::Etl::pair<elg_int32, elg_float32> Int32Float32Pair;  // NOLINT(build/include_what_you_use)
  Int32Float32Pair q = Elg::Utilities::Etl::make_pair_ref(-2, 1.0f);

  CHECK_EQUAL(-2, q.first);
  CHECK_EQUAL(1.0, q.second);
}
