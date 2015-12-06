/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

#include "Elg.Tests/Utilities/ETL/TestIterator.h"

#include "Elg/Utilities/ETL/Algorithm.h"

TEST(Etl_Algorithm_Minimum) {
  elg_int32 a = 1;
  elg_int32 b = 2;
  CHECK(a == Elg::Utilities::Etl::minimum(a, b));
  CHECK(a == Elg::Utilities::Etl::minimum(b, a));

  elg_float64 c = -1.1;
  elg_float64 d = 2.2;
  CHECK(c == Elg::Utilities::Etl::minimum(c, d));
  CHECK(c == Elg::Utilities::Etl::minimum(d, c));
}

TEST(Etl_Algorithm_Minimum_Compare) {
  struct Comparator {
    bool operator()(const elg_int32& lhs, const elg_int32& rhs) const {
      return (lhs > rhs);
    }

    bool operator()(const elg_float64& lhs, const elg_float64& rhs) const {
      return (lhs > rhs);
    }
  };

  Comparator cmp;

  elg_int32 a = 1;
  elg_int32 b = 2;
  CHECK(b == Elg::Utilities::Etl::minimum(a, b, cmp));
  CHECK(b == Elg::Utilities::Etl::minimum(b, a, cmp));

  elg_float64 c = -1.1;
  elg_float64 d = 2.2;
  CHECK(d == Elg::Utilities::Etl::minimum(c, d, cmp));
  CHECK(d == Elg::Utilities::Etl::minimum(d, c, cmp));
}

TEST(Etl_Algorithm_Maximum) {
  elg_int32 a = 1;
  elg_int32 b = 2;
  CHECK(b == Elg::Utilities::Etl::maximum(a, b));
  CHECK(b == Elg::Utilities::Etl::maximum(b, a));

  elg_float64 c = -1.1;
  elg_float64 d = 2.2;
  CHECK(d == Elg::Utilities::Etl::maximum(c, d));
  CHECK(d == Elg::Utilities::Etl::maximum(d, c));
}

TEST(Etl_Algorithm_Maximum_Compare) {
  struct Comparator {
    bool operator()(const elg_int32& lhs, const elg_int32& rhs) const {
      return (lhs > rhs);
    }

    bool operator()(const elg_float64& lhs, const elg_float64& rhs) const {
      return (lhs > rhs);
    }
  };

  Comparator cmp;

  elg_int32 a = 1;
  elg_int32 b = 2;
  CHECK(a == Elg::Utilities::Etl::maximum(a, b, cmp));
  CHECK(a == Elg::Utilities::Etl::maximum(b, a, cmp));

  elg_float64 c = -1.1;
  elg_float64 d = 2.2;
  CHECK(c == Elg::Utilities::Etl::maximum(c, d, cmp));
  CHECK(c == Elg::Utilities::Etl::maximum(d, c, cmp));
}

TEST(Etl_Algorithm_MinElement) {
  elg_int32 a[] = {1, 2, -2, 3, -1};
  CHECK_EQUAL(a + 2, Elg::Utilities::Etl::min_element(a, a + 5));
}

TEST(Etl_Algorithm_MinElement_Compare) {
  struct Comparator {
    bool operator()(const elg_int32& lhs, const elg_int32& rhs) const {
      return (lhs > rhs);
    }

    bool operator()(const elg_float64& lhs, const elg_float64& rhs) const {
      return (lhs > rhs);
    }
  };

  Comparator cmp;
  elg_int32 a[] = {1, 2, -2, 3, -1};
  CHECK_EQUAL(a + 3, Elg::Utilities::Etl::min_element(a, a + 5, cmp));
}

TEST(Etl_Algorithm_MaxElement) {
  elg_int32 a[] = {1, 2, -2, 3, -1};
  CHECK_EQUAL(a + 3, Elg::Utilities::Etl::max_element(a, a + 5));
}

TEST(Etl_Algorithm_MaxElement_Compare) {
  struct Comparator {
    bool operator()(const elg_int32& lhs, const elg_int32& rhs) const {
      return (lhs > rhs);
    }

    bool operator()(const elg_float64& lhs, const elg_float64& rhs) const {
      return (lhs > rhs);
    }
  };

  Comparator cmp;
  elg_int32 a[] = {1, 2, -2, 3, -1};
  CHECK_EQUAL(a + 2, Elg::Utilities::Etl::max_element(a, a + 5, cmp));
}

TEST(Etl_Algorithm_Median) {
  elg_int32 a = 3;
  elg_int32 b = -2;
  elg_int32 c = 1;
  CHECK_EQUAL(1, Elg::Utilities::Etl::median(a, b, c));
}

TEST(Etl_Algorithm_Median_Compare) {
  struct Comparator {
    bool operator()(const elg_int32& lhs, const elg_int32& rhs) const {
      return (lhs > rhs);
    }

    bool operator()(const elg_float64& lhs, const elg_float64& rhs) const {
      return (lhs > rhs);
    }
  };

  elg_int32 a = 3;
  elg_int32 b = -2;
  elg_int32 c = 1;
  CHECK_EQUAL(1, Elg::Utilities::Etl::median(a, b, c));
}

TEST(Etl_Algorithm_Swap) {
  struct TestStructure {
    TestStructure(elg_int32 x, elg_int32 y) : X(x), Y(y) {
    }

    elg_int32 X;
    elg_int32 Y;
  };

  TestStructure a(1, 3);
  TestStructure b(2, 0);

  Elg::Utilities::Etl::swap(a, b);

  CHECK_EQUAL(2, a.X);
  CHECK_EQUAL(0, a.Y);

  CHECK_EQUAL(1, b.X);
  CHECK_EQUAL(3, b.Y);
}

TEST(Etl_Algorithm_IterSwap) {
  struct TestStructure {
    explicit TestStructure(elg_int32 x) : X(x) {
    }

    operator elg_int32() {
      return X;
    }

    TestStructure& operator=(const elg_int32& rhs) {
      X = rhs;
      return *this;
    }

    elg_int32 X;
  };

  TestStructure a(1);
  TestStructure b(2);
  elg_int32 c = 3;

  Elg::Utilities::Etl::iter_swap(&a, &b);

  CHECK_EQUAL(2, a.X);
  CHECK_EQUAL(1, b.X);

  Elg::Utilities::Etl::iter_swap(&a, &c);

  CHECK_EQUAL(3, a.X);
  CHECK_EQUAL(2, c);
}

TEST(Etl_Algorithm_SwapRanges) {
  elg_int32 a[] = {1, 2, 3};
  elg_int32 b[] = {-1, -2, -3};

  Elg::Utilities::Etl::swap_ranges(a, a+3, b);

  CHECK_EQUAL(-1, a[0]);
  CHECK_EQUAL(-2, a[1]);
  CHECK_EQUAL(-3, a[2]);

  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(3, b[2]);
}

TEST(Etl_Algorithm_AdjecentFind) {
  elg_int32 a[] = {10, 20, 30, 30, 20, 10, 10, 20};
  elg_int32* result;

  result = Elg::Utilities::Etl::adjacent_find(a, a + 8);
  CHECK(a + 2 == result);

  result = Elg::Utilities::Etl::adjacent_find(result + 1, a + 8);
  CHECK(a + 5 == result);

  result = Elg::Utilities::Etl::adjacent_find(result + 1, a + 8);
  CHECK(a + 8 == result);
}

TEST(Etl_Algorithm_AdjecentFind_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 a, elg_int32 b) {
      return (a != b);
    }
  };

  elg_int32 a[] = {10, 10, 20, 20, 20, 30, 30, 30};
  elg_int32* result;

  Predicate pred;

  result = Elg::Utilities::Etl::adjacent_find(a, a + 8, pred);
  CHECK(a + 1 == result);

  result = Elg::Utilities::Etl::adjacent_find(result + 1, a + 8, pred);
  CHECK(a + 4 == result);

  result = Elg::Utilities::Etl::adjacent_find(result + 1, a + 8, pred);
  CHECK(a + 8 == result);
}

TEST(Etl_Algorithm_Copy_CopyChooser) {
  // A trivial copy and random iterator (we don't test overlapping ranges)
  elg_int32 a[] = {1, 2, 0, 0};

  Elg::Utilities::Etl::copy_chooser(a, a + 2, a + 2);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(2, a[1]);
  CHECK_EQUAL(1, a[2]);
  CHECK_EQUAL(2, a[3]);

  // A trivial copy and bidirectional iterator (we don't test overlapping ranges)
  elg_int32 b[] = {1, 2, 0, 0};

  TestBidirectionalIterator first(b);
  TestBidirectionalIterator second(b + 1);
  TestBidirectionalIterator third(b + 2);
  TestBidirectionalIterator fourth(b + 3);

  Elg::Utilities::Etl::copy_chooser(first, third, third);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(1, b[2]);
  CHECK_EQUAL(2, b[3]);
}

TEST(Etl_Algorithm_Copy) {
  // No generic iterators
  elg_int32 a[] = {1, 2, 0, 0};

  Elg::Utilities::Etl::copy(a, a + 2, a + 2);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(2, a[1]);
  CHECK_EQUAL(1, a[2]);
  CHECK_EQUAL(2, a[3]);

  // Source generic iterator
  elg_int32 b[] = {1, 2, 0, 0};
  Elg::Utilities::Etl::generic_iterator<elg_int32*> b_source_start(b);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> b_source_end(b + 2);

  Elg::Utilities::Etl::copy(b_source_start, b_source_end, b + 2);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(1, b[2]);
  CHECK_EQUAL(2, b[3]);

  // Destination generic iterator
  elg_int32 c[] = {1, 2, 0, 0};
  Elg::Utilities::Etl::generic_iterator<elg_int32*> c_dest(c + 2);

  Elg::Utilities::Etl::copy(c, c + 2, c_dest);
  CHECK_EQUAL(1, c[0]);
  CHECK_EQUAL(2, c[1]);
  CHECK_EQUAL(1, c[2]);
  CHECK_EQUAL(2, c[3]);

  // Source and destination generic iterator
  elg_int32 d[] = {1, 2, 0, 0};
  Elg::Utilities::Etl::generic_iterator<elg_int32*> d_source_start(d);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> d_source_end(d + 2);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> d_dest(d + 2);

  Elg::Utilities::Etl::copy(d_source_start, d_source_end, d_dest);
  CHECK_EQUAL(1, d[0]);
  CHECK_EQUAL(2, d[1]);
  CHECK_EQUAL(1, d[2]);
  CHECK_EQUAL(2, d[3]);
}

TEST(Etl_Algorithm_CopyBackward_CopyBackwardChooser) {
  // A trivial copy and random iterator (we don't test overlapping ranges)
  elg_int32 a[] = {1, 2, 0, 0};

  Elg::Utilities::Etl::copy_backward_chooser(a, a + 2, a + 4);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(2, a[1]);
  CHECK_EQUAL(1, a[2]);
  CHECK_EQUAL(2, a[3]);

  Elg::Utilities::Etl::copy_backward_chooser(a + 1, a + 3, a + 4);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(2, a[1]);
  CHECK_EQUAL(2, a[2]);
  CHECK_EQUAL(1, a[3]);

  // A trivial copy and bidirectional iterator (we don't test overlapping ranges)
  elg_int32 b[] = {1, 2, 0, 0};

  TestBidirectionalIterator first(b);
  TestBidirectionalIterator second(b + 1);
  TestBidirectionalIterator third(b + 2);
  TestBidirectionalIterator fourth(b + 3);
  TestBidirectionalIterator end(b + 4);

  Elg::Utilities::Etl::copy_backward_chooser(first, third, end);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(1, b[2]);
  CHECK_EQUAL(2, b[3]);

  Elg::Utilities::Etl::copy_backward_chooser(second, fourth, end);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(2, b[2]);
  CHECK_EQUAL(1, b[3]);
}

TEST(Etl_Algorithm_CopyBackward) {
  // No generic iterators
  elg_int32 a[] = {1, 2, 0, 0};

  Elg::Utilities::Etl::copy_backward(a, a + 2, a + 4);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(2, a[1]);
  CHECK_EQUAL(1, a[2]);
  CHECK_EQUAL(2, a[3]);

  // Source generic iterator
  elg_int32 b[] = {1, 2, 0, 0};
  Elg::Utilities::Etl::generic_iterator<elg_int32*> b_source_start(b);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> b_source_end(b + 2);

  Elg::Utilities::Etl::copy_backward(b_source_start, b_source_end, b + 4);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(1, b[2]);
  CHECK_EQUAL(2, b[3]);

  // Destination generic iterator
  elg_int32 c[] = {1, 2, 0, 0};
  Elg::Utilities::Etl::generic_iterator<elg_int32*> c_dest(c + 4);

  Elg::Utilities::Etl::copy_backward(c, c + 2, c_dest);
  CHECK_EQUAL(1, c[0]);
  CHECK_EQUAL(2, c[1]);
  CHECK_EQUAL(1, c[2]);
  CHECK_EQUAL(2, c[3]);

  // Source and destination generic iterator
  elg_int32 d[] = {1, 2, 0, 0};
  Elg::Utilities::Etl::generic_iterator<elg_int32*> d_source_start(d);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> d_source_end(d + 2);
  Elg::Utilities::Etl::generic_iterator<elg_int32*> d_dest(d + 4);

  Elg::Utilities::Etl::copy_backward(d_source_start, d_source_end, d_dest);
  CHECK_EQUAL(1, d[0]);
  CHECK_EQUAL(2, d[1]);
  CHECK_EQUAL(1, d[2]);
  CHECK_EQUAL(2, d[3]);
}

TEST(Etl_Algorithm_Count) {
  elg_int32 a[] = {1, 2, 0, 2, 1, 0, 1};
  CHECK_EQUAL(2, Elg::Utilities::Etl::count(a, a + 7, 0));
  CHECK_EQUAL(3, Elg::Utilities::Etl::count(a, a + 7, 1));
  CHECK_EQUAL(2, Elg::Utilities::Etl::count(a, a + 7, 2));
}

TEST(Etl_Algorithm_Count_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::unary_function<elg_int32, bool> {
    explicit Predicate(elg_int32 x) : X(x) {
    }

    bool operator()(elg_int32 v) {
      return (X == v);
    }

    elg_int32 X;
  };

  elg_int32 a[] = {1, 2, 0, 2, 1, 0, 1};

  CHECK_EQUAL(2, Elg::Utilities::Etl::count_if(a, a + 7, Predicate(0)));
  CHECK_EQUAL(3, Elg::Utilities::Etl::count_if(a, a + 7, Predicate(1)));
  CHECK_EQUAL(2, Elg::Utilities::Etl::count_if(a, a + 7, Predicate(2)));
}

TEST(Etl_Algorithm_Fill) {
  // Test for scalars
  elg_int32 a[3];
  Elg::Utilities::Etl::fill(a, a+3, 123);
  CHECK_EQUAL(123, a[0]);
  CHECK_EQUAL(123, a[1]);
  CHECK_EQUAL(123, a[2]);

  // Check for non-scalar type
  struct TestStruct {
    TestStruct() : X(0) {
    }

    explicit TestStruct(elg_int32 x) : X(x) {
    }

    elg_int32 X;
  };

  TestStruct b[3];
  Elg::Utilities::Etl::fill(b, b+3, TestStruct(123));
  CHECK_EQUAL(123, b[0].X);
  CHECK_EQUAL(123, b[1].X);
  CHECK_EQUAL(123, b[2].X);
}

TEST(Etl_Algorithm_Fill_Specialisations) {
  // Check elg_char implementation
  elg_char char_array[3];
  Elg::Utilities::Etl::fill(char_array, char_array + 3, static_cast<elg_char>('A'));
  CHECK_EQUAL('A', char_array[0]);
  CHECK_EQUAL('A', char_array[1]);
  CHECK_EQUAL('A', char_array[2]);

  Elg::Utilities::Etl::fill(char_array, char_array + 3, static_cast<elg_int32>('B'));
  CHECK_EQUAL('B', char_array[0]);
  CHECK_EQUAL('B', char_array[1]);
  CHECK_EQUAL('B', char_array[2]);

  // Check elg_uchar implementation
  elg_uchar uchar_array[3];
  Elg::Utilities::Etl::fill(uchar_array, uchar_array + 3, static_cast<elg_uchar>('A'));
  CHECK_EQUAL('A', uchar_array[0]);
  CHECK_EQUAL('A', uchar_array[1]);
  CHECK_EQUAL('A', uchar_array[2]);

  Elg::Utilities::Etl::fill(uchar_array, uchar_array + 3, static_cast<elg_int32>('B'));
  CHECK_EQUAL('B', uchar_array[0]);
  CHECK_EQUAL('B', uchar_array[1]);
  CHECK_EQUAL('B', uchar_array[2]);

  // Check elg_schar implementation
  elg_schar schar_array[3];
  Elg::Utilities::Etl::fill(schar_array, schar_array + 3, static_cast<elg_schar>('A'));
  CHECK_EQUAL('A', schar_array[0]);
  CHECK_EQUAL('A', schar_array[1]);
  CHECK_EQUAL('A', schar_array[2]);

  Elg::Utilities::Etl::fill(schar_array, schar_array + 3, static_cast<elg_int32>('B'));
  CHECK_EQUAL('B', schar_array[0]);
  CHECK_EQUAL('B', schar_array[1]);
  CHECK_EQUAL('B', schar_array[2]);

  // Check bool implementation
  bool bool_array[3];
  Elg::Utilities::Etl::fill(bool_array, bool_array + 3, true);
  CHECK_EQUAL(true, bool_array[0]);
  CHECK_EQUAL(true, bool_array[1]);
  CHECK_EQUAL(true, bool_array[2]);

  Elg::Utilities::Etl::fill(bool_array, bool_array + 3, false);
  CHECK_EQUAL(false, bool_array[0]);
  CHECK_EQUAL(false, bool_array[1]);
  CHECK_EQUAL(false, bool_array[2]);
}

TEST(Etl_Algorithm_FillN) {
  // Test for scalars
  elg_int32 a[3] = {0, 0, 0};
  Elg::Utilities::Etl::fill_n(a, 2, 123);
  CHECK_EQUAL(123, a[0]);
  CHECK_EQUAL(123, a[1]);
  CHECK_EQUAL(0, a[2]);

  // Check for non-scalar type
  struct TestStruct {
    TestStruct() : X(0) {
    }

    explicit TestStruct(elg_int32 x) : X(x) {
    }

    elg_int32 X;
  };

  TestStruct b[3];
  Elg::Utilities::Etl::fill_n(b, 2, TestStruct(123));
  CHECK_EQUAL(123, b[0].X);
  CHECK_EQUAL(123, b[1].X);
  CHECK_EQUAL(0, b[2].X);
}

TEST(Etl_Algorithm_FillN_Specialisations) {
  // Check elg_char implementation
  elg_char char_array[3] = {'Z', 'Z', 'Z'};
  Elg::Utilities::Etl::fill_n(char_array, 2, static_cast<elg_char>('A'));
  CHECK_EQUAL('A', char_array[0]);
  CHECK_EQUAL('A', char_array[1]);
  CHECK_EQUAL('Z', char_array[2]);

  // Check elg_uchar implementation
  elg_uchar uchar_array[3] = {'Z', 'Z', 'Z'};
  Elg::Utilities::Etl::fill_n(uchar_array, 2, static_cast<elg_uchar>('A'));
  CHECK_EQUAL('A', uchar_array[0]);
  CHECK_EQUAL('A', uchar_array[1]);
  CHECK_EQUAL('Z', uchar_array[2]);

  // Check elg_schar implementation
  elg_schar schar_array[3] = {'Z', 'Z', 'Z'};
  Elg::Utilities::Etl::fill_n(schar_array, 2, static_cast<elg_schar>('A'));
  CHECK_EQUAL('A', schar_array[0]);
  CHECK_EQUAL('A', schar_array[1]);
  CHECK_EQUAL('Z', schar_array[2]);

  // Check bool implementation
  bool bool_array[3] = {false, false, false};
  Elg::Utilities::Etl::fill_n(bool_array, 2, true);
  CHECK_EQUAL(true, bool_array[0]);
  CHECK_EQUAL(true, bool_array[1]);
  CHECK_EQUAL(false, bool_array[2]);

  Elg::Utilities::Etl::fill_n(bool_array, 2, false);
  CHECK_EQUAL(false, bool_array[0]);
  CHECK_EQUAL(false, bool_array[1]);
  CHECK_EQUAL(false, bool_array[2]);
}

TEST(Etl_Algorithm_Find) {
  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32* result;

  result = Elg::Utilities::Etl::find(a, a + 5, 3);
  CHECK(result == a + 4);

  result = Elg::Utilities::Etl::find(a, a + 5, 4);
  CHECK(result == a);

  result = Elg::Utilities::Etl::find(a, a + 5, 2);
  CHECK(result == a + 1);

  result = Elg::Utilities::Etl::find(a, a + 5, 10);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_FindIf) {
  struct Predicate : public Elg::Utilities::Etl::unary_function<elg_int32, bool> {
    explicit Predicate(elg_int32 x) : X(x) {
    }

    bool operator()(elg_int32 value) const {
      return (value > X);
    }

    elg_int32 X;
  };

  elg_int32 a[] = {2, 1, 0, 4, 3};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_if(a, a + 5, Predicate(3));
  CHECK(result == a + 3);

  result = Elg::Utilities::Etl::find_if(a, a + 5, Predicate(0));
  CHECK(result == a);

  result = Elg::Utilities::Etl::find_if(a, a + 5, Predicate(2));
  CHECK(result == a + 3);

  result = Elg::Utilities::Etl::find_if(a, a + 5, Predicate(10));
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_FindFirstOf) {
  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {2, 1};
  elg_int32 c[] = {1, 3};
  elg_int32 d[] = {5, -1};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_first_of(a, a + 5, b, b + 2);
  CHECK(result == a + 1);

  result = Elg::Utilities::Etl::find_first_of(a, a + 5, c, c + 2);
  CHECK(result == a + 2);

  result = Elg::Utilities::Etl::find_first_of(a, a + 5, d, d + 2);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_FindFirstOf_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {2, -1};
  elg_int32 c[] = {-1, 3};
  elg_int32 d[] = {5, -6};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_first_of(a, a + 5, b, b + 2, pred);
  CHECK(result == a + 1);

  result = Elg::Utilities::Etl::find_first_of(a, a + 5, c, c + 2, pred);
  CHECK(result == a + 2);

  result = Elg::Utilities::Etl::find_first_of(a, a + 5, d, d + 2, pred);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_FindFirstNotOf) {
  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {2, 1};
  elg_int32 c[] = {4, 5};
  elg_int32 d[] = {2, 4};
  elg_int32 e[] = {3, 0, 2, 1, 4};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, b, b + 2);
  CHECK(result == a);

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, c, c + 2);
  CHECK(result == a + 1);

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, d, d + 2);
  CHECK(result == a + 2);

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, e, e + 5);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_FindFirstNotOf_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {-2, -1};
  elg_int32 c[] = {-4, -5};
  elg_int32 d[] = {-2, -4};
  elg_int32 e[] = {-3, 0, -2, -1, -4};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, b, b + 2, pred);
  CHECK(result == a);

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, c, c + 2, pred);
  CHECK(result == a + 1);

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, d, d + 2, pred);
  CHECK(result == a + 2);

  result = Elg::Utilities::Etl::find_first_not_of(a, a + 5, e, e + 5, pred);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_FindLastOf) {
  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {2, 1};
  elg_int32 c[] = {1, 3};
  elg_int32 d[] = {5, -1};
  elg_int32 e[] = {4, -1};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, b, b + 2);
  CHECK(result == a + 2);

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, c, c + 2);
  CHECK(result == a + 4);

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, d, d + 2);
  CHECK(result == a + 5);

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, e, e + 2);
  CHECK(result == a);
}

TEST(Etl_Algorithm_FindLastOf_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {-2, -1};
  elg_int32 c[] = {-1, -3};
  elg_int32 d[] = {-5, 10};
  elg_int32 e[] = {-4, 10};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, b, b + 2, pred);
  CHECK(result == a + 2);

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, c, c + 2, pred);
  CHECK(result == a + 4);

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, d, d + 2, pred);
  CHECK(result == a + 5);

  result = Elg::Utilities::Etl::find_last_of(a, a + 5, e, e + 2, pred);
  CHECK(result == a);
}

TEST(Etl_Algorithm_FindLastNotOf) {
  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {2, 1};
  elg_int32 c[] = {1, 3};
  elg_int32 d[] = {0, 3, 2, 1};
  elg_int32 e[] = {3, 0, 2, 1, 4};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, b, b + 2);
  CHECK(result == a + 4);

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, c, c + 2);
  CHECK(result == a + 3);

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, d, d + 4);
  CHECK(result == a);

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, e, e + 5);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_FindLastNotOf_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a[] = {4, 2, 1, 0, 3};
  elg_int32 b[] = {-2, -1};
  elg_int32 c[] = {-1, -3};
  elg_int32 d[] = {0, -3, -2, -1};
  elg_int32 e[] = {-3, 0, -2, -1, -4};
  elg_int32* result;

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, b, b + 2, pred);
  CHECK(result == a + 4);

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, c, c + 2, pred);
  CHECK(result == a + 3);

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, d, d + 4, pred);
  CHECK(result == a);

  result = Elg::Utilities::Etl::find_last_not_of(a, a + 5, e, e + 5, pred);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_ForEach) {
  struct Function : public Elg::Utilities::Etl::unary_function<elg_int32&, void> {
    void operator()(elg_int32& x) {  // NOLINT(runtime/references)
      x = x*x;
    }
  };

  Function fun;

  elg_int32 a[] = {4, 2, 1, 0, 3};
  Elg::Utilities::Etl::for_each(a, a+5, fun);

  CHECK_EQUAL(16, a[0]);
  CHECK_EQUAL(4, a[1]);
  CHECK_EQUAL(1, a[2]);
  CHECK_EQUAL(0, a[3]);
  CHECK_EQUAL(9, a[4]);
}

TEST(Etl_Algorithm_Generate) {
  struct Genrator {
    Genrator() : X(0) {
    }

    elg_int32 operator()() {
      elg_int32 result = (X-1)*(X+1);
      ++X;
      return result;
    }

    elg_int32 X;
  };

  Genrator gen;

  elg_int32 a[] = {0, 0, 0, 0, 0};
  Elg::Utilities::Etl::generate(a, a+5, gen);

  CHECK_EQUAL(-1, a[0]);
  CHECK_EQUAL(0, a[1]);
  CHECK_EQUAL(3, a[2]);
  CHECK_EQUAL(8, a[3]);
  CHECK_EQUAL(15, a[4]);
}

TEST(Etl_Algorithm_GenerateN) {
  struct Genrator {
    Genrator() : X(0) {
    }

    elg_int32 operator()() {
      elg_int32 result = (X-1)*(X+1);
      ++X;
      return result;
    }

    elg_int32 X;
  };

  Genrator gen;

  elg_int32 a[] = {0, 0, 0, 0, 0};
  Elg::Utilities::Etl::generate_n(a, 3, gen);

  CHECK_EQUAL(-1, a[0]);
  CHECK_EQUAL(0, a[1]);
  CHECK_EQUAL(3, a[2]);
  CHECK_EQUAL(0, a[3]);
  CHECK_EQUAL(0, a[4]);
}

TEST(Etl_Algorithm_Transform_Unary) {
  struct Transform : public Elg::Utilities::Etl::unary_function<elg_int32, elg_int32> {
    elg_int32 operator()(elg_int32 x) {
      return (x-1)*(x+1);
    }
  };

  Transform trans;

  elg_int32 a[] = {0, 1, 2, 3, 4};
  elg_int32 b[] = {0, 0, 0, 0, 0};
  Elg::Utilities::Etl::transform(a, a + 5, b, trans);

  CHECK_EQUAL(-1, b[0]);
  CHECK_EQUAL(0, b[1]);
  CHECK_EQUAL(3, b[2]);
  CHECK_EQUAL(8, b[3]);
  CHECK_EQUAL(15, b[4]);
}

TEST(Etl_Algorithm_Transform_Binary) {
  struct Transform : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, elg_int32> {
    elg_int32 operator()(elg_int32 x, elg_int32 y) {
      return (x-1)*(y+1);
    }
  };

  Transform trans;

  elg_int32 a[] = {0, 1, 2, 3, 4};
  elg_int32 b[] = {4, 3, 2, 1, 0};
  elg_int32 c[] = {0, 0, 0, 0, 0};

  Elg::Utilities::Etl::transform(a, a + 5, b, c, trans);  // NOLINT(build/include_what_you_use)

  CHECK_EQUAL(-5, c[0]);
  CHECK_EQUAL(0, c[1]);
  CHECK_EQUAL(3, c[2]);
  CHECK_EQUAL(4, c[3]);
  CHECK_EQUAL(3, c[4]);
}

TEST(Etl_Algorithm_Equal) {
  elg_int32 a1[] = {0, 1, 2, 3, 4};
  elg_int32 b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::equal(a1, a1 + 5, b1));

  elg_int32 a2[] = {0, 1, 2, 3, 4};
  elg_int32 b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::equal(a2, a2 + 5, b2));

  elg_int32 a3[] = {0, 1, 2, 3, 4};
  elg_int32 b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(false, Elg::Utilities::Etl::equal(a3, a3 + 5, b3));

  elg_int32 a4[] = {0, 1, 2, 3, 4};
  elg_int32 b4[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::equal(a4, a4 + 5, b4));
}

TEST(Etl_Algorithm_Equal_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a1[] = {0, 1, -2, 3, -4};
  elg_int32 b1[] = {5, -1, 2, -3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::equal(a1, a1 + 5, b1, pred));

  elg_int32 a2[] = {0, 1, -2, 3, -4};
  elg_int32 b2[] = {0, -1, 5, -3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::equal(a2, a2 + 5, b2, pred));

  elg_int32 a3[] = {0, 1, -2, 3, -4};
  elg_int32 b3[] = {0, -1, 2, -3, 5};
  CHECK_EQUAL(false, Elg::Utilities::Etl::equal(a3, a3 + 5, b3, pred));

  elg_int32 a4[] = {0, 1, -2, 3, -4};
  elg_int32 b4[] = {0, -1, 2, -3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::equal(a4, a4 + 5, b4, pred));
}

TEST(Etl_Algorithm_Identical) {
  elg_int32 a1[] = {0, 1, 2, 3, 4};
  elg_int32 b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a1, a1 + 5, b1, b1 + 5));

  elg_int32 a2[] = {0, 1, 2, 3, 4};
  elg_int32 b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a2, a2 + 5, b2, b2 + 5));

  elg_int32 a3[] = {0, 1, 2, 3, 4};
  elg_int32 b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a3, a3 + 5, b3, b3 + 5));

  elg_int32 a4[] = {0, 1, 2, 3, 4};
  elg_int32 b4[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::identical(a4, a4 + 5, b4, b4 + 5));

  elg_int32 a5[] = {0, 1, 2, 3};
  elg_int32 b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a5, a5 + 4, b5, b5+ 5));

  elg_int32 a6[] = {0, 1, 2, 3, 4};
  elg_int32 b6[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a6, a6 + 5, b6, b6 + 4));
}

TEST(Etl_Algorithm_Identical_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a1[] = {0, 1, 2, 3, 4};
  elg_int32 b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a1, a1 + 5, b1, b1 + 5, pred));

  elg_int32 a2[] = {0, 1, 2, 3, 4};
  elg_int32 b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a2, a2 + 5, b2, b2 + 5, pred));

  elg_int32 a3[] = {0, 1, 2, 3, 4};
  elg_int32 b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a3, a3 + 5, b3, b3 + 5, pred));

  elg_int32 a4[] = {0, 1, 2, 3, 4};
  elg_int32 b4[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::identical(a4, a4 + 5, b4, b4 + 5, pred));

  elg_int32 a5[] = {0, 1, 2, 3};
  elg_int32 b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a5, a5 + 4, b5, b5 + 5, pred));

  elg_int32 a6[] = {0, 1, 2, 3, 4};
  elg_int32 b6[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::identical(a6, a6 + 5, b6, b6 + 4, pred));
}

TEST(Etl_Algorithm_LexicographicalCompare) {
  // LHS smaller
  elg_int32 a1[] = {0, 1, 2, 3, 4};
  elg_int32 b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5));

  elg_int32 a2[] = {0, 1, 2, 3, 4};
  elg_int32 b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5));

  elg_int32 a3[] = {0, 1, 2, 3, 4};
  elg_int32 b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5));

  elg_int32 a4[] = {0, 1, 2, 3};
  elg_int32 b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5));

  // Both equal
  elg_int32 a5[] = {0, 1, 2, 3, 4};
  elg_int32 b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5));

  // RHS smaller
  elg_int32 a6[] = {5, 1, 2, 3, 4};
  elg_int32 b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5));

  elg_int32 a7[] = {0, 1, 5, 3, 4};
  elg_int32 b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5));

  elg_int32 a8[] = {0, 1, 2, 3, 5};
  elg_int32 b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5));

  elg_int32 a9[] = {0, 1, 2, 3, 4};
  elg_int32 b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4));
}

TEST(Etl_Algorithm_LexicographicalCompare_Specialisation_ConstChar) {
  // LHS smaller
  const elg_char a1[] = {0, 1, 2, 3, 4};
  const elg_char b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5));

  const elg_char a2[] = {0, 1, 2, 3, 4};
  const elg_char b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5));

  const elg_char a3[] = {0, 1, 2, 3, 4};
  const elg_char b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5));

  const elg_char a4[] = {0, 1, 2, 3};
  const elg_char b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5));

  // Both equal
  const elg_char a5[] = {0, 1, 2, 3, 4};
  const elg_char b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5));

  // RHS smaller
  const elg_char a6[] = {5, 1, 2, 3, 4};
  const elg_char b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5));

  const elg_char a7[] = {0, 1, 5, 3, 4};
  const elg_char b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5));

  const elg_char a8[] = {0, 1, 2, 3, 5};
  const elg_char b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5));

  const elg_char a9[] = {0, 1, 2, 3, 4};
  const elg_char b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4));
}

TEST(Etl_Algorithm_LexicographicalCompare_Specialisation_Char) {
  // LHS smaller
  elg_char a1[] = {0, 1, 2, 3, 4};
  elg_char b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5));

  elg_char a2[] = {0, 1, 2, 3, 4};
  elg_char b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5));

  elg_char a3[] = {0, 1, 2, 3, 4};
  elg_char b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5));

  elg_char a4[] = {0, 1, 2, 3};
  elg_char b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5));

  // Both equal
  elg_char a5[] = {0, 1, 2, 3, 4};
  elg_char b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5));

  // RHS smaller
  elg_char a6[] = {5, 1, 2, 3, 4};
  elg_char b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5));

  elg_char a7[] = {0, 1, 5, 3, 4};
  elg_char b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5));

  elg_char a8[] = {0, 1, 2, 3, 5};
  elg_char b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5));

  elg_char a9[] = {0, 1, 2, 3, 4};
  elg_char b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4));
}

TEST(Etl_Algorithm_LexicographicalCompare_Specialisation_ConstUChar) {
  // LHS smaller
  const elg_uchar a1[] = {0, 1, 2, 3, 4};
  const elg_uchar b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5));

  const elg_uchar a2[] = {0, 1, 2, 3, 4};
  const elg_uchar b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5));

  const elg_uchar a3[] = {0, 1, 2, 3, 4};
  const elg_uchar b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5));

  const elg_uchar a4[] = {0, 1, 2, 3};
  const elg_uchar b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5));

  // Both equal
  const elg_uchar a5[] = {0, 1, 2, 3, 4};
  const elg_uchar b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5));

  // RHS smaller
  const elg_uchar a6[] = {5, 1, 2, 3, 4};
  const elg_uchar b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5));

  const elg_uchar a7[] = {0, 1, 5, 3, 4};
  const elg_uchar b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5));

  const elg_uchar a8[] = {0, 1, 2, 3, 5};
  const elg_uchar b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5));

  const elg_uchar a9[] = {0, 1, 2, 3, 4};
  const elg_uchar b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4));
}

TEST(Etl_Algorithm_LexicographicalCompare_Specialisation_UChar) {
  // LHS smaller
  elg_uchar a1[] = {0, 1, 2, 3, 4};
  elg_uchar b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5));

  elg_uchar a2[] = {0, 1, 2, 3, 4};
  elg_uchar b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5));

  elg_uchar a3[] = {0, 1, 2, 3, 4};
  elg_uchar b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5));

  elg_uchar a4[] = {0, 1, 2, 3};
  elg_uchar b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5));

  // Both equal
  elg_uchar a5[] = {0, 1, 2, 3, 4};
  elg_uchar b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5));

  // RHS smaller
  elg_uchar a6[] = {5, 1, 2, 3, 4};
  elg_uchar b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5));

  elg_uchar a7[] = {0, 1, 5, 3, 4};
  elg_uchar b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5));

  elg_uchar a8[] = {0, 1, 2, 3, 5};
  elg_uchar b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5));

  elg_uchar a9[] = {0, 1, 2, 3, 4};
  elg_uchar b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4));
}

TEST(Etl_Algorithm_LexicographicalCompare_Specialisation_ConstSChar) {
  // LHS smaller
  const elg_schar a1[] = {0, 1, 2, 3, 4};
  const elg_schar b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5));

  const elg_schar a2[] = {0, 1, 2, 3, 4};
  const elg_schar b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5));

  const elg_schar a3[] = {0, 1, 2, 3, 4};
  const elg_schar b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5));

  const elg_schar a4[] = {0, 1, 2, 3};
  const elg_schar b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5));

  // Both equal
  const elg_schar a5[] = {0, 1, 2, 3, 4};
  const elg_schar b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5));

  // RHS smaller
  const elg_schar a6[] = {5, 1, 2, 3, 4};
  const elg_schar b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5));

  const elg_schar a7[] = {0, 1, 5, 3, 4};
  const elg_schar b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5));

  const elg_schar a8[] = {0, 1, 2, 3, 5};
  const elg_schar b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5));

  const elg_schar a9[] = {0, 1, 2, 3, 4};
  const elg_schar b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4));
}

TEST(Etl_Algorithm_LexicographicalCompare_Specialisation_SChar) {
  // LHS smaller
  elg_schar a1[] = {0, 1, 2, 3, 4};
  elg_schar b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5));

  elg_schar a2[] = {0, 1, 2, 3, 4};
  elg_schar b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5));

  elg_schar a3[] = {0, 1, 2, 3, 4};
  elg_schar b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5));

  elg_schar a4[] = {0, 1, 2, 3};
  elg_schar b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5));

  // Both equal
  elg_schar a5[] = {0, 1, 2, 3, 4};
  elg_schar b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5));

  // RHS smaller
  elg_schar a6[] = {5, 1, 2, 3, 4};
  elg_schar b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5));

  elg_schar a7[] = {0, 1, 5, 3, 4};
  elg_schar b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5));

  elg_schar a8[] = {0, 1, 2, 3, 5};
  elg_schar b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5));

  elg_schar a9[] = {0, 1, 2, 3, 4};
  elg_schar b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4));
}

TEST(Etl_Algorithm_LexicographicalCompare_Predicate) {
  struct Comparator {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > rhs);
    }
  };

  Comparator cmp;

  // LHS smaller
  elg_int32 a1[] = {0, 1, 2, 3, 4};
  elg_int32 b1[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a1, a1 + 5, b1, b1 + 5, cmp));

  elg_int32 a2[] = {0, 1, 2, 3, 4};
  elg_int32 b2[] = {0, 1, 5, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a2, a2 + 5, b2, b2 + 5, cmp));

  elg_int32 a3[] = {0, 1, 2, 3, 4};
  elg_int32 b3[] = {0, 1, 2, 3, 5};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a3, a3 + 5, b3, b3 + 5, cmp));

  elg_int32 a4[] = {0, 1, 2, 3};
  elg_int32 b4[] = {5, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a4, a4 + 4, b4, b4 + 5, cmp));

  // Both equal
  elg_int32 a5[] = {0, 1, 2, 3, 4};
  elg_int32 b5[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a5, a5 + 5, b5, b5 + 5, cmp));

  // RHS smaller
  elg_int32 a6[] = {5, 1, 2, 3, 4};
  elg_int32 b6[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a6, a6 + 5, b6, b6 + 5, cmp));

  elg_int32 a7[] = {0, 1, 5, 3, 4};
  elg_int32 b7[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a7, a7 + 5, b7, b7 + 5, cmp));

  elg_int32 a8[] = {0, 1, 2, 3, 5};
  elg_int32 b8[] = {0, 1, 2, 3, 4};
  CHECK_EQUAL(true, Elg::Utilities::Etl::lexicographical_compare(a8, a8 + 5, b8, b8 + 5, cmp));

  elg_int32 a9[] = {0, 1, 2, 3, 4};
  elg_int32 b9[] = {0, 1, 2, 3};
  CHECK_EQUAL(false, Elg::Utilities::Etl::lexicographical_compare(a9, a9 + 5, b9, b9 + 4, cmp));  // Since its shorter
}

TEST(Etl_Algorithm_LowerBound) {
  // We need a sorted range
  elg_int32 a[] = {0, 1, 1, 4, 5, 7, 7, 7, 9, 10};
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, -1) == a);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 0) == a);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 1) == a + 1);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 2) == a + 3);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 3) == a + 3);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 4) == a + 3);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 5) == a + 4);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 6) == a + 5);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 7) == a + 5);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 8) == a + 8);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 9) == a + 8);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 10) == a + 9);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 11) == a + 10);

  // Try an empty range
  CHECK(Elg::Utilities::Etl::lower_bound(a, a, -1) == a);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a, 5) == a);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a, 11) == a);
}

TEST(Etl_Algorithm_LowerBound_Compare) {
  struct Comparator {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) < (rhs > 0 ? rhs : -rhs);
    }
  };

  Comparator cmp;

  // We need a sorted range
  elg_int32 a[] = {0, 1, 1, 4, 5, 7, 7, 7, 9, 10};
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, -1, cmp) == a + 1);  // We do comparison with abs value
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 0, cmp) == a);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 1, cmp) == a + 1);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 2, cmp) == a + 3);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 3, cmp) == a + 3);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 4, cmp) == a + 3);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 5, cmp) == a + 4);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 6, cmp) == a + 5);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 7, cmp) == a + 5);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 8, cmp) == a + 8);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 9, cmp) == a + 8);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 10, cmp) == a + 9);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a + 10, 11, cmp) == a + 10);

  // Try an empty range
  CHECK(Elg::Utilities::Etl::lower_bound(a, a, -1, cmp) == a);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a, 5, cmp) == a);
  CHECK(Elg::Utilities::Etl::lower_bound(a, a, 11, cmp) == a);
}

TEST(Etl_Algorithm_UpperBound) {
  // We need a sorted range
  elg_int32 a[] = {0, 1, 1, 4, 5, 7, 7, 7, 9, 10};
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, -1) == a);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 0) == a + 1);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 1) == a + 3);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 2) == a + 3);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 3) == a + 3);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 4) == a + 4);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 5) == a + 5);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 6) == a + 5);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 7) == a + 8);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 8) == a + 8);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 9) == a + 9);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 10) == a + 10);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 11) == a + 10);

  // Try an empty range
  CHECK(Elg::Utilities::Etl::upper_bound(a, a, -1) == a);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a, 5) == a);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a, 11) == a);
}

TEST(Etl_Algorithm_UpperBound_Compare) {
  struct Comparator {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) < (rhs > 0 ? rhs : -rhs);
    }
  };

  Comparator cmp;

  // We need a sorted range
  elg_int32 a[] = {0, 1, 1, 4, 5, 7, 7, 7, 9, 10};
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, -1, cmp) == a + 3);  // We do comparison with abs value
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 0, cmp) == a + 1);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 1, cmp) == a + 3);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 2, cmp) == a + 3);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 3, cmp) == a + 3);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 4, cmp) == a + 4);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 5, cmp) == a + 5);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 6, cmp) == a + 5);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 7, cmp) == a + 8);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 8, cmp) == a + 8);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 9, cmp) == a + 9);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 10, cmp) == a + 10);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a + 10, 11, cmp) == a + 10);

  // Try an empty range
  CHECK(Elg::Utilities::Etl::upper_bound(a, a, -1, cmp) == a);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a, 5, cmp) == a);
  CHECK(Elg::Utilities::Etl::upper_bound(a, a, 11, cmp) == a);
}

TEST(Etl_Algorithm_EqualRange) {
  // We need a sorted range
  elg_int32 a[] = {0, 1, 1, 4, 5, 7, 7, 7, 9, 10};
  Elg::Utilities::Etl::pair<elg_int32*, elg_int32*> result;

  // Non empty range
  result = Elg::Utilities::Etl::equal_range(a, a + 10, -1);
  CHECK(result.first == a);
  CHECK(result.second == a);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 0);
  CHECK(result.first == a);
  CHECK(result.second == a + 1);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 1);
  CHECK(result.first == a + 1);
  CHECK(result.second == a + 3);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 2);
  CHECK(result.first == a + 3);
  CHECK(result.second == a + 3);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 3);
  CHECK(result.first == a + 3);
  CHECK(result.second == a + 3);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 4);
  CHECK(result.first == a + 3);
  CHECK(result.second == a + 4);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 5);
  CHECK(result.first == a + 4);
  CHECK(result.second == a + 5);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 6);
  CHECK(result.first == a + 5);
  CHECK(result.second == a + 5);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 7);
  CHECK(result.first == a + 5);
  CHECK(result.second == a + 8);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 8);
  CHECK(result.first == a + 8);
  CHECK(result.second == a + 8);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 9);
  CHECK(result.first == a + 8);
  CHECK(result.second == a + 9);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 10);
  CHECK(result.first == a + 9);
  CHECK(result.second == a + 10);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 11);
  CHECK(result.first == a + 10);
  CHECK(result.second == a + 10);

  // Try an empty range
  result = Elg::Utilities::Etl::equal_range(a, a, -1);
  CHECK(result.first == a);
  CHECK(result.second == a);

  result = Elg::Utilities::Etl::equal_range(a, a, 5);
  CHECK(result.first == a);
  CHECK(result.second == a);

  result = Elg::Utilities::Etl::equal_range(a, a, 11);
  CHECK(result.first == a);
  CHECK(result.second == a);
}

TEST(Etl_Algorithm_EqualRange_Compare) {
  struct Comparator {
    bool operator()(elg_int32 lhs, elg_int32 rhs) const {
      return (lhs > 0 ? lhs : -lhs) < (rhs > 0 ? rhs : -rhs);
    }
  };

  Comparator cmp;

  // We need a sorted range
  elg_int32 a[] = {0, 1, 1, 4, 5, 7, 7, 7, 9, 10};
  Elg::Utilities::Etl::pair<elg_int32*, elg_int32*> result;  // NOLINT(build/include_what_you_use)

  // Non empty range
  result = Elg::Utilities::Etl::equal_range(a, a + 10, -1, cmp);  // We compare by abs value
  CHECK(result.first == a + 1);
  CHECK(result.second == a + 3);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 0, cmp);
  CHECK(result.first == a);
  CHECK(result.second == a + 1);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 1, cmp);
  CHECK(result.first == a + 1);
  CHECK(result.second == a + 3);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 2, cmp);
  CHECK(result.first == a + 3);
  CHECK(result.second == a + 3);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 3, cmp);
  CHECK(result.first == a + 3);
  CHECK(result.second == a + 3);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 4, cmp);
  CHECK(result.first == a + 3);
  CHECK(result.second == a + 4);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 5, cmp);
  CHECK(result.first == a + 4);
  CHECK(result.second == a + 5);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 6, cmp);
  CHECK(result.first == a + 5);
  CHECK(result.second == a + 5);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 7, cmp);
  CHECK(result.first == a + 5);
  CHECK(result.second == a + 8);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 8, cmp);
  CHECK(result.first == a + 8);
  CHECK(result.second == a + 8);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 9, cmp);
  CHECK(result.first == a + 8);
  CHECK(result.second == a + 9);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 10, cmp);
  CHECK(result.first == a + 9);
  CHECK(result.second == a + 10);

  result = Elg::Utilities::Etl::equal_range(a, a + 10, 11, cmp);
  CHECK(result.first == a + 10);
  CHECK(result.second == a + 10);

  // Try an empty range
  result = Elg::Utilities::Etl::equal_range(a, a, -1, cmp);
  CHECK(result.first == a);
  CHECK(result.second == a);

  result = Elg::Utilities::Etl::equal_range(a, a, 5, cmp);
  CHECK(result.first == a);
  CHECK(result.second == a);

  result = Elg::Utilities::Etl::equal_range(a, a, 11, cmp);
  CHECK(result.first == a);
  CHECK(result.second == a);
}

TEST(Etl_Algorithm_Replace) {
  elg_int32 a[] = {0, 1, 2, 3, 4};

  Elg::Utilities::Etl::replace(a, a + 5, 1, 2);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(2, a[1]);
  CHECK_EQUAL(2, a[2]);
  CHECK_EQUAL(3, a[3]);
  CHECK_EQUAL(4, a[4]);

  Elg::Utilities::Etl::replace(a, a + 5, 2, 3);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(3, a[1]);
  CHECK_EQUAL(3, a[2]);
  CHECK_EQUAL(3, a[3]);
  CHECK_EQUAL(4, a[4]);
}

TEST(Etl_Algorithm_ReplaceIf) {
  struct Predicate : public Elg::Utilities::Etl::unary_function<elg_int32, bool> {
    explicit Predicate(elg_int32 x) : X(x) {
    }

    bool operator()(elg_int32 value) {
      return (0 < value) && (value < X);
    }

    elg_int32 X;
  };

  elg_int32 a[] = {0, 1, 2, 3, 4};

  Elg::Utilities::Etl::replace_if(a, a + 5, Predicate(2), 2);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(2, a[1]);
  CHECK_EQUAL(2, a[2]);
  CHECK_EQUAL(3, a[3]);
  CHECK_EQUAL(4, a[4]);

  Elg::Utilities::Etl::replace_if(a, a + 5, Predicate(3), 3);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(3, a[1]);
  CHECK_EQUAL(3, a[2]);
  CHECK_EQUAL(3, a[3]);
  CHECK_EQUAL(4, a[4]);
}

TEST(Etl_Algorithm_RemoveCopy) {
  elg_int32 a[] = {1, 2, 3, 2, 1};
  elg_int32 b[] = {0, 0, 0, 0, 0};
  elg_int32* result;

  result = Elg::Utilities::Etl::remove_copy(a, a + 5, b, 2);
  CHECK(result == b + 3);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(3, b[1]);
  CHECK_EQUAL(1, b[2]);
  CHECK_EQUAL(0, b[3]);
  CHECK_EQUAL(0, b[4]);

  result = Elg::Utilities::Etl::remove_copy(a, a + 5, b, 3);
  CHECK(result == b + 4);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(2, b[2]);
  CHECK_EQUAL(1, b[3]);
  CHECK_EQUAL(0, b[4]);
}

TEST(Etl_Algorithm_RemoveCopyIf) {
  struct Predicate : public Elg::Utilities::Etl::unary_function<elg_int32, bool> {
    Predicate(elg_int32 lbound, elg_int32 ubound) : LBound(lbound), UBound(ubound) {
    }

    bool operator()(elg_int32 value) {
      return (LBound < value) && (value < UBound);
    }

    elg_int32 LBound;
    elg_int32 UBound;
  };

  elg_int32 a[] = {1, 2, 3, 2, 1};
  elg_int32 b[] = {0, 0, 0, 0, 0};
  elg_int32* result;

  result = Elg::Utilities::Etl::remove_copy_if(a, a + 5, b, Predicate(1, 4));
  CHECK(result == b + 2);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(1, b[1]);
  CHECK_EQUAL(0, b[2]);
  CHECK_EQUAL(0, b[3]);
  CHECK_EQUAL(0, b[4]);

  result = Elg::Utilities::Etl::remove_copy_if(a, a + 5, b, Predicate(1, 3));
  CHECK(result == b + 3);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(3, b[1]);
  CHECK_EQUAL(1, b[2]);
  CHECK_EQUAL(0, b[3]);
  CHECK_EQUAL(0, b[4]);
}

TEST(Etl_Algorithm_Remove) {
  elg_int32 a[] = {1, 2, 3, 2, 1};
  elg_int32* result;

  result = Elg::Utilities::Etl::remove(a, a + 5, 2);
  CHECK(result == a + 3);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(3, a[1]);
  CHECK_EQUAL(1, a[2]);

  result = Elg::Utilities::Etl::remove(a, a + 3, 3);
  CHECK(result == a + 2);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(1, a[1]);
}

TEST(Etl_Algorithm_RemoveIf) {
  struct Predicate : public Elg::Utilities::Etl::unary_function<elg_int32, bool> {
    Predicate(elg_int32 lbound, elg_int32 ubound) : LBound(lbound), UBound(ubound) {
    }

    bool operator()(elg_int32 value) {
      return (LBound < value) && (value < UBound);
    }

    elg_int32 LBound;
    elg_int32 UBound;
  };

  elg_int32 a[] = {1, 2, 3, 2, 1};
  elg_int32* result;

  result = Elg::Utilities::Etl::remove_if(a, a + 5, Predicate(1, 3));
  CHECK(result == a + 3);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(3, a[1]);
  CHECK_EQUAL(1, a[2]);

  result = Elg::Utilities::Etl::remove_if(a, a + 3, Predicate(2, 4));
  CHECK(result == a + 2);
  CHECK_EQUAL(1, a[0]);
  CHECK_EQUAL(1, a[1]);
}

TEST(Etl_Algorithm_ReplaceCopy) {
  elg_int32 a[] = {1, 2, 3, 2, 1};
  elg_int32 b[] = {0, 0, 0, 0, 0};
  elg_int32* result;

  result = Elg::Utilities::Etl::replace_copy(a, a + 5, b, 2, 5);
  CHECK(result == b + 5);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(5, b[1]);
  CHECK_EQUAL(3, b[2]);
  CHECK_EQUAL(5, b[3]);
  CHECK_EQUAL(1, b[4]);

  result = Elg::Utilities::Etl::replace_copy(a, a + 5, b, 3, 6);
  CHECK(result == b + 5);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(2, b[1]);
  CHECK_EQUAL(6, b[2]);
  CHECK_EQUAL(2, b[3]);
  CHECK_EQUAL(1, b[4]);
}

TEST(Etl_Algorithm_ReplcaeCopyIf) {
  struct Predicate : public Elg::Utilities::Etl::unary_function<elg_int32, bool> {
    Predicate(elg_int32 lbound, elg_int32 ubound) : LBound(lbound), UBound(ubound) {
    }

    bool operator()(elg_int32 value) {
      return (LBound < value) && (value < UBound);
    }

    elg_int32 LBound;
    elg_int32 UBound;
  };

  elg_int32 a[] = {1, 2, 3, 2, 1};
  elg_int32 b[] = {0, 0, 0, 0, 0};
  elg_int32* result;

  result = Elg::Utilities::Etl::replace_copy_if(a, a + 5, b, Predicate(1, 3), 5);
  CHECK(result == b + 5);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(5, b[1]);
  CHECK_EQUAL(3, b[2]);
  CHECK_EQUAL(5, b[3]);
  CHECK_EQUAL(1, b[4]);

  result = Elg::Utilities::Etl::replace_copy_if(a, a + 5, b, Predicate(1, 6), 6);
  CHECK(result == b + 5);
  CHECK_EQUAL(1, b[0]);
  CHECK_EQUAL(6, b[1]);
  CHECK_EQUAL(6, b[2]);
  CHECK_EQUAL(6, b[3]);
  CHECK_EQUAL(1, b[4]);
}

TEST(Etl_Algorithm_Reverse) {
  elg_int32 a[] = {1, 2, 3, 4, 5};

  TestBidirectionalIterator beginning(a);
  TestBidirectionalIterator end(a + 5);
  Elg::Utilities::Etl::reverse(beginning, end);
  CHECK_EQUAL(5, a[0]);
  CHECK_EQUAL(4, a[1]);
  CHECK_EQUAL(3, a[2]);
  CHECK_EQUAL(2, a[3]);
  CHECK_EQUAL(1, a[4]);

  Elg::Utilities::Etl::reverse(a, a + 3);
  CHECK_EQUAL(3, a[0]);
  CHECK_EQUAL(4, a[1]);
  CHECK_EQUAL(5, a[2]);
  CHECK_EQUAL(2, a[3]);
  CHECK_EQUAL(1, a[4]);
}

TEST(Etl_Algorithm_ReverseCopy) {
  elg_int32 a[] = {1, 2, 3, 4, 5};
  elg_int32 b[] = {0, 0, 0, 0, 0};
  elg_int32* result;

  result = Elg::Utilities::Etl::reverse_copy(a, a+5, b);
  CHECK(result == b + 5);
  CHECK_EQUAL(5, b[0]);
  CHECK_EQUAL(4, b[1]);
  CHECK_EQUAL(3, b[2]);
  CHECK_EQUAL(2, b[3]);
  CHECK_EQUAL(1, b[4]);
}

TEST(Etl_Algorithm_Search) {
  elg_int32 a[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 5, 6, 7, 8, 9};
  elg_int32* result;

  elg_int32 b1[] = {0, 1, 2};
  result = Elg::Utilities::Etl::search(a, a + 14, b1, b1 + 3);
  CHECK(result == a);

  elg_int32 b2[] = {3, 5, 6};
  result = Elg::Utilities::Etl::search(a, a + 14, b2, b2 + 3);
  CHECK(result == a + 8);

  elg_int32 b3[] = {7, 8, 9};
  result = Elg::Utilities::Etl::search(a, a + 14, b3, b3 + 3);
  CHECK(result == a + 11);

  // Empty range
  result = Elg::Utilities::Etl::search(a, a + 14, b3, b3);
  CHECK(result == a);

  elg_int32 b5[] = {0, 1, 3};
  result = Elg::Utilities::Etl::search(a, a + 14, b5, b5 + 3);
  CHECK(result == a + 14);

  elg_int32 b6[] = {4, 7, 6};
  result = Elg::Utilities::Etl::search(a, a + 14, b6, b6 + 3);
  CHECK(result == a + 14);

  elg_int32 b7[] = {8, 9, 10};
  result = Elg::Utilities::Etl::search(a, a + 14, b7, b7 + 3);
  CHECK(result == a + 14);
}

TEST(Etl_Algorithm_Search_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a[] = {0, -1, 2, -3, 4, 0, 1, -2, 3, -5, 6, -7, 8, -9};
  elg_int32* result;

  elg_int32 b1[] = {0, 1, -2};
  result = Elg::Utilities::Etl::search(a, a + 14, b1, b1 + 3, pred);
  CHECK(result == a);

  elg_int32 b2[] = {-3, 5, -6};
  result = Elg::Utilities::Etl::search(a, a + 14, b2, b2 + 3, pred);
  CHECK(result == a + 8);

  elg_int32 b3[] = {-7, 8, -9};
  result = Elg::Utilities::Etl::search(a, a + 14, b3, b3 + 3, pred);
  CHECK(result == a + 11);

  // Empty range
  result = Elg::Utilities::Etl::search(a, a + 14, b3, b3, pred);
  CHECK(result == a);

  elg_int32 b5[] = {0, 1, -3};
  result = Elg::Utilities::Etl::search(a, a + 14, b5, b5 + 3, pred);
  CHECK(result == a + 14);

  elg_int32 b6[] = {-4, 7, -6};
  result = Elg::Utilities::Etl::search(a, a + 14, b6, b6 + 3, pred);
  CHECK(result == a + 14);

  elg_int32 b7[] = {-8, 9, -10};
  result = Elg::Utilities::Etl::search(a, a + 14, b7, b7 + 3, pred);
  CHECK(result == a + 14);
}

TEST(Etl_Algorithm_SearchN) {
  elg_int32 a[] = {10, 20, 30, 30, 30, 20, 10, 10, 20};

  // Random access iterators
  elg_int32* result1;
  result1 = Elg::Utilities::Etl::search_n(a, a + 9, 1, 30);
  CHECK(result1 == a + 2);

  result1 = Elg::Utilities::Etl::search_n(a, a + 9, 2, 30);
  CHECK(result1 == a + 2);

  result1 = Elg::Utilities::Etl::search_n(a, a + 9, 3, 10);
  CHECK(result1 == a + 9);

  result1 = Elg::Utilities::Etl::search_n(a, a + 9, 1, 10);
  CHECK(result1 == a);

  result1 = Elg::Utilities::Etl::search_n(a, a + 9, 2, 10);
  CHECK(result1 == a + 6);

  result1 = Elg::Utilities::Etl::search_n(a, a + 9, 3, 10);
  CHECK(result1 == a + 9);

  // Forward iterator
  TestForwardIterator result2;
  result2 = Elg::Utilities::Etl::search_n(TestForwardIterator(a), TestForwardIterator(a + 9), 1, 30);
  CHECK(result2.base() == a + 2);

  result2 = Elg::Utilities::Etl::search_n(TestForwardIterator(a), TestForwardIterator(a + 9), 2, 30);
  CHECK(result2.base() == a + 2);

  result2 = Elg::Utilities::Etl::search_n(TestForwardIterator(a), TestForwardIterator(a + 9), 3, 10);
  CHECK(result2.base() == a + 9);

  result2 = Elg::Utilities::Etl::search_n(TestForwardIterator(a), TestForwardIterator(a + 9), 1, 10);
  CHECK(result2.base() == a);

  result2 = Elg::Utilities::Etl::search_n(TestForwardIterator(a), TestForwardIterator(a + 9), 2, 10);
  CHECK(result2.base() == a + 6);

  result2 = Elg::Utilities::Etl::search_n(TestForwardIterator(a), TestForwardIterator(a + 9), 3, 10);
  CHECK(result2.base() == a + 9);
}

TEST(Etl_Algorithm_BinarySearch) {
  elg_int32 a[] = {0, 1, 2, 5, 6};

  CHECK_EQUAL(true, Elg::Utilities::Etl::binary_search(a, a + 5, 6));
  CHECK_EQUAL(true, Elg::Utilities::Etl::binary_search(a, a + 5, 0));
  CHECK_EQUAL(true, Elg::Utilities::Etl::binary_search(a, a + 5, 1));
  CHECK_EQUAL(false, Elg::Utilities::Etl::binary_search(a, a + 5, -1));
  CHECK_EQUAL(false, Elg::Utilities::Etl::binary_search(a, a + 5, 3));
  CHECK_EQUAL(false, Elg::Utilities::Etl::binary_search(a, a + 5, 10));
}

TEST(Etl_Algorithm_BinarySearch_Compare) {
  struct Compare {
    bool operator()(elg_int32 lhs, elg_int32 rhs) {
      return (lhs > rhs);
    }
  };

  Compare cmp;

  elg_int32 a[] = {6, 5, 2, 1, 0};

  CHECK_EQUAL(true, Elg::Utilities::Etl::binary_search(a, a + 5, 6, cmp));
  CHECK_EQUAL(true, Elg::Utilities::Etl::binary_search(a, a + 5, 0, cmp));
  CHECK_EQUAL(true, Elg::Utilities::Etl::binary_search(a, a + 5, 1, cmp));
  CHECK_EQUAL(false, Elg::Utilities::Etl::binary_search(a, a + 5, -1, cmp));
  CHECK_EQUAL(false, Elg::Utilities::Etl::binary_search(a, a + 5, 3, cmp));
  CHECK_EQUAL(false, Elg::Utilities::Etl::binary_search(a, a + 5, 10, cmp));
}

TEST(Etl_Algorithm_BinarySearchIt) {
  elg_int32 a[] = {0, 1, 2, 5, 6};
  elg_int32* result;

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 6);
  CHECK(result == a + 4);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 0);
  CHECK(result == a);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 1);
  CHECK(result == a + 1);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, -1);
  CHECK(result == a + 5);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 3);
  CHECK(result == a + 5);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 10);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_BinarySearchIt_Compare) {
  struct Compare {
    bool operator()(elg_int32 lhs, elg_int32 rhs) {
      return (lhs > rhs);
    }
  };

  Compare cmp;

  elg_int32 a[] = {6, 5, 2, 1, 0};
  elg_int32* result;

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 6, cmp);
  CHECK(result == a);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 0, cmp);
  CHECK(result == a + 4);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 1, cmp);
  CHECK(result == a + 3);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, -1, cmp);
  CHECK(result == a + 5);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 3, cmp);
  CHECK(result == a + 5);

  result = Elg::Utilities::Etl::binary_search_it(a, a + 5, 10, cmp);
  CHECK(result == a + 5);
}

TEST(Etl_Algorithm_Unique) {
  elg_int32 a[] = {0, 1, 1, 4, 5, 7, 7, 7, 9, 10};

  elg_int32* result1 = Elg::Utilities::Etl::unique(a, a + 10);
  CHECK(result1 == a + 7);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(1, a[1]);
  CHECK_EQUAL(4, a[2]);
  CHECK_EQUAL(5, a[3]);
  CHECK_EQUAL(7, a[4]);
  CHECK_EQUAL(9, a[5]);
  CHECK_EQUAL(10, a[6]);

  elg_int32* result2 = Elg::Utilities::Etl::unique(a, result1);
  CHECK(result1 == result2);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(1, a[1]);
  CHECK_EQUAL(4, a[2]);
  CHECK_EQUAL(5, a[3]);
  CHECK_EQUAL(7, a[4]);
  CHECK_EQUAL(9, a[5]);
  CHECK_EQUAL(10, a[6]);

  elg_int32* result3 = Elg::Utilities::Etl::unique(a, a);
  CHECK(result3 == a);
}

TEST(Etl_Algorithm_Unique_Predicate) {
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> {
    bool operator()(elg_int32 lhs, elg_int32 rhs) {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a[] = {0, 1, -1, 4, -5, 7, -7, 7, -9, 10};

  elg_int32* result1 = Elg::Utilities::Etl::unique(a, a + 10, pred);
  CHECK(result1 == a + 7);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(1, a[1]);
  CHECK_EQUAL(4, a[2]);
  CHECK_EQUAL(-5, a[3]);
  CHECK_EQUAL(7, a[4]);
  CHECK_EQUAL(-9, a[5]);
  CHECK_EQUAL(10, a[6]);

  elg_int32* result2 = Elg::Utilities::Etl::unique(a, result1, pred);
  CHECK(result1 == result2);
  CHECK_EQUAL(0, a[0]);
  CHECK_EQUAL(1, a[1]);
  CHECK_EQUAL(4, a[2]);
  CHECK_EQUAL(-5, a[3]);
  CHECK_EQUAL(7, a[4]);
  CHECK_EQUAL(-9, a[5]);
  CHECK_EQUAL(10, a[6]);

  elg_int32* result3 = Elg::Utilities::Etl::unique(a, a, pred);
  CHECK(result3 == a);
}

TEST(Etl_Algorithm_FindEnd) {
  elg_int32 a[] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 5, 6, 7, 8, 9};
  elg_int32* result;

  elg_int32 b1[] = {0, 1, 2};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b1, b1 + 3);
  CHECK(result == a + 5);

  elg_int32 b2[] = {3, 5, 6};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b2, b2 + 3);
  CHECK(result == a + 8);

  elg_int32 b3[] = {1, 2, 3};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b3, b3 + 3);
  CHECK(result == a + 6);

  // Empty range
  result = Elg::Utilities::Etl::find_end(a, a + 14, b3, b3);
  CHECK(result == a + 14);

  elg_int32 b5[] = {0, 1, 3};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b5, b5 + 3);
  CHECK(result == a + 14);

  elg_int32 b6[] = {4, 7, 6};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b6, b6 + 3);
  CHECK(result == a + 14);

  elg_int32 b7[] = {8, 9, 10};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b7, b7 + 3);
  CHECK(result == a + 14);
}

TEST(Etl_Algorithm_FindEnd_Predicate) {
  typedef Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, bool> Base;  // NOLINT(build/include_what_you_use)
  struct Predicate : public Base {
    bool operator()(elg_int32 lhs, elg_int32 rhs) {
      return (lhs > 0 ? lhs : -lhs) == (rhs > 0 ? rhs : -rhs);
    }
  };

  Predicate pred;

  elg_int32 a[] = {0, -1, 2, -3, 4, 0, 1, -2, 3, -5, 6, -7, 8, -9};
  elg_int32* result;

  elg_int32 b1[] = {0, 1, 2};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b1, b1 + 3, pred);
  CHECK(result == a + 5);

  elg_int32 b2[] = {3, 5, 6};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b2, b2 + 3, pred);
  CHECK(result == a + 8);

  elg_int32 b3[] = {1, 2, 3};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b3, b3 + 3, pred);
  CHECK(result == a + 6);

  // Empty range
  result = Elg::Utilities::Etl::find_end(a, a + 14, b3, b3, pred);
  CHECK(result == a + 14);

  elg_int32 b5[] = {0, 1, 3};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b5, b5 + 3, pred);
  CHECK(result == a + 14);

  elg_int32 b6[] = {4, 7, 6};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b6, b6 + 3, pred);
  CHECK(result == a + 14);

  elg_int32 b7[] = {8, 9, 10};
  result = Elg::Utilities::Etl::find_end(a, a + 14, b7, b7 + 3, pred);
  CHECK(result == a + 14);
}

TEST(Etl_Algorithm_SetDifference) {
  elg_int32* result;

  elg_int32 a1[] = {0, 0, 1, 2, 3, 4, 4, 4, 5, 6, 7};
  elg_int32 b1[] = {0, 0, 1, 2, 3, 4, 4, 4, 5, 6, 7};
  elg_int32 c1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a1, a1 + 11, b1, b1 + 11, c1);
  CHECK(result == c1);

  elg_int32 a2[] = {0, 0, 1, 2, 3, 4, 4, 4, 5, 6, 7};
  elg_int32 b2[] = {0, 2, 3, 4, 4, 5, 7};
  elg_int32 c2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a2, a2 + 11, b2, b2 + 7, c2);
  CHECK(result == c2 + 4);
  CHECK_EQUAL(0, c2[0]);
  CHECK_EQUAL(1, c2[1]);
  CHECK_EQUAL(4, c2[2]);
  CHECK_EQUAL(6, c2[3]);

  elg_int32 a3[] = {0, 0, 1, 2, 3, 4, 4, 4, 5, 6, 7};
  elg_int32 b3[] = {-1, 0, 0, 4, 4, 4, 10};
  elg_int32 c3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a3, a3 + 11, b3, b3 + 7, c3);
  CHECK(result == c3 + 6);
  CHECK_EQUAL(1, c3[0]);
  CHECK_EQUAL(2, c3[1]);
  CHECK_EQUAL(3, c3[2]);
  CHECK_EQUAL(5, c3[3]);
  CHECK_EQUAL(6, c3[4]);
  CHECK_EQUAL(7, c3[5]);

  elg_int32 a4[] = {0, 0, 1, 2, 3, 4, 4, 4, 5, 6, 7};
  elg_int32 c4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a4, a4 + 11, b3, b3, c4);
  CHECK(result == c4 + 11);
  CHECK_EQUAL(0, c4[0]);
  CHECK_EQUAL(0, c4[1]);
  CHECK_EQUAL(1, c4[2]);
  CHECK_EQUAL(2, c4[3]);
  CHECK_EQUAL(3, c4[4]);
  CHECK_EQUAL(4, c4[5]);
  CHECK_EQUAL(4, c4[6]);
  CHECK_EQUAL(4, c4[7]);
  CHECK_EQUAL(5, c4[8]);
  CHECK_EQUAL(6, c4[9]);
  CHECK_EQUAL(7, c4[10]);

  elg_int32 b5[] = {1, 2, 3, 4};
  elg_int32 c5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a4, a4, b5, b5, c5);
  CHECK(result == c5);
}

TEST(Etl_Algorithm_SetDifference_Compare) {
  struct Compare {
    bool operator()(elg_int32 lhs, elg_int32 rhs) {
      return (lhs > rhs);
    }
  };

  Compare cmp;

  elg_int32* result;

  elg_int32 a1[] = {7, 6, 5, 4, 4, 4, 3, 2, 1, 0, 0};
  elg_int32 b1[] = {7, 6, 5, 4, 4, 4, 3, 2, 1, 0, 0};
  elg_int32 c1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a1, a1 + 11, b1, b1 + 11, c1, cmp);
  CHECK(result == c1);

  elg_int32 a2[] = {7, 6, 5, 4, 4, 4, 3, 2, 1, 0, 0};
  elg_int32 b2[] = {7, 5, 4, 4, 3, 2, 0};
  elg_int32 c2[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a2, a2 + 11, b2, b2 + 7, c2, cmp);
  CHECK(result == c2 + 4);
  CHECK_EQUAL(6, c2[0]);
  CHECK_EQUAL(4, c2[1]);
  CHECK_EQUAL(1, c2[2]);
  CHECK_EQUAL(0, c2[3]);

  elg_int32 a3[] = {7, 6, 5, 4, 4, 4, 3, 2, 1, 0, 0};
  elg_int32 b3[] = {10, 4, 4, 4, 0, 0, -1};
  elg_int32 c3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a3, a3 + 11, b3, b3 + 7, c3, cmp);
  CHECK(result == c3 + 6);
  CHECK_EQUAL(7, c3[0]);
  CHECK_EQUAL(6, c3[1]);
  CHECK_EQUAL(5, c3[2]);
  CHECK_EQUAL(3, c3[3]);
  CHECK_EQUAL(2, c3[4]);
  CHECK_EQUAL(1, c3[5]);

  elg_int32 a4[] = {7, 6, 5, 4, 4, 4, 3, 2, 1, 0, 0};
  elg_int32 c4[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a4, a4 + 11, b3, b3, c4, cmp);
  CHECK(result == c4 + 11);
  CHECK_EQUAL(7, c4[0]);
  CHECK_EQUAL(6, c4[1]);
  CHECK_EQUAL(5, c4[2]);
  CHECK_EQUAL(4, c4[3]);
  CHECK_EQUAL(4, c4[4]);
  CHECK_EQUAL(4, c4[5]);
  CHECK_EQUAL(3, c4[6]);
  CHECK_EQUAL(2, c4[7]);
  CHECK_EQUAL(1, c4[8]);
  CHECK_EQUAL(0, c4[9]);
  CHECK_EQUAL(0, c4[10]);

  elg_int32 b5[] = {4, 3, 2, 1};
  elg_int32 c5[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  result = Elg::Utilities::Etl::set_difference(a4, a4, b5, b5, c5, cmp);
  CHECK(result == c5);
}
