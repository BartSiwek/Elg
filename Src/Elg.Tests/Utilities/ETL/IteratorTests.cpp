/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/ETL/TypeTraits.h"
#include "Elg/Utilities/ETL/Utility.h"

#include "Elg.Tests/Utilities/ETL/TestIterator.h"

#include "Elg/Utilities/ETL/Iterator.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper class - a dummy container
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct DummyContainer {
  enum LastAction {
    LAST_ACTION_NONE = 0,
    LAST_ACTION_PUSH_FRONT = 1,
    LAST_ACTION_PUSH_BACK = 2,
    LAST_ACTION_INSERT = 3,
  };

  typedef T*       iterator;
  typedef const T* const_iterator;
  typedef T&       reference;
  typedef const T& const_reference;

  DummyContainer()
    : Value(), Action(LAST_ACTION_NONE), InsertionPoint(NULL) {
  }

  T* begin() {
    return static_cast<T*>(NULL);
  }

  T* end() {
    return static_cast<T*>(NULL);
  }

  void push_back(const T& value) {
    Value = value;
    Action = LAST_ACTION_PUSH_BACK;
    InsertionPoint = NULL;
  }

  void push_front(const T& value) {
    Value = value;
    Action = LAST_ACTION_PUSH_FRONT;
    InsertionPoint = NULL;
  }

  T* insert(T* position, const T& value) {
    Value = value;
    Action = LAST_ACTION_INSERT;
    InsertionPoint = position;

    return InsertionPoint;
  }

  T Value;
  LastAction Action;
  T* InsertionPoint;
};

////////////////////////////////
// Tests
////////////////////////////////
TEST(Etl_Iterators_ReverseIterator_Construction) {
  // Helper variables
  elg_int32 test_array[] = {1, 2, 3, 4, 5};
  elg_int32* test_iterator = test_array + 2;

  // Test the iterator
  Elg::Utilities::Etl::reverse_iterator<elg_int32*> default_contructed;
  CHECK_EQUAL(static_cast<elg_int32*>(NULL) - 1, &*(default_contructed));

  Elg::Utilities::Etl::reverse_iterator<elg_int32*> iterator_constructed(test_iterator);
  CHECK(&*(test_iterator - 1) == &*(iterator_constructed));

  Elg::Utilities::Etl::reverse_iterator<elg_int32*> copy_constructed(default_contructed);
  CHECK(&*(default_contructed) == &*(copy_constructed));

  // DummyRandomIterator wraps a elg_int32 pointer
  Elg::Utilities::Etl::reverse_iterator<TestRandomIterator> other_constructed(iterator_constructed);
  CHECK(&*(iterator_constructed) == &*(other_constructed));
}

TEST(Etl_Iterators_ReverseIterator_Operations) {
  // Typedefs
  typedef Elg::Utilities::Etl::pair<elg_int32, elg_int32> ValueType;
  typedef ValueType* IteratorType;

  // Helper variables
  ValueType test_array[] = { Elg::Utilities::Etl::pair<elg_int32, elg_int32>(1, -1),
                             Elg::Utilities::Etl::pair<elg_int32, elg_int32>(2, -2),
                             Elg::Utilities::Etl::pair<elg_int32, elg_int32>(3, -3),
                             Elg::Utilities::Etl::pair<elg_int32, elg_int32>(4, -4),
                             Elg::Utilities::Etl::pair<elg_int32, elg_int32>(5, -5) };
  IteratorType random_iterator = test_array + 3;

  // Construct the iterator
  Elg::Utilities::Etl::reverse_iterator<IteratorType> reverse_iterator(random_iterator);

  // Test the iterator - operator=
  Elg::Utilities::Etl::reverse_iterator<IteratorType> default_reverse_constructed;
  default_reverse_constructed = reverse_iterator;
  CHECK(&*(default_reverse_constructed) == &*(reverse_iterator));

  // Test the iterator - base
  CHECK(random_iterator == reverse_iterator.base());

  // Test the iterator - operator*
  CHECK(*(random_iterator - 1) == *reverse_iterator);

  // Test the iterator - operator->
  CHECK((random_iterator - 1)->first == reverse_iterator->first);
  CHECK((random_iterator - 1)->second == reverse_iterator->second);

  // Operator ++
  ++reverse_iterator;
  CHECK(&*(random_iterator - 2) == &*(reverse_iterator));

  // Operator --
  --reverse_iterator;
  CHECK(&*(random_iterator - 1) == &*(reverse_iterator));

  // Operator ++ (postfix)
  Elg::Utilities::Etl::reverse_iterator<IteratorType> postfix_inc_prev = reverse_iterator++;
  CHECK(&*(random_iterator - 2) == &*(reverse_iterator));
  CHECK(&*(random_iterator - 1) == &*(postfix_inc_prev));

  // Operator -- (postfix)
  Elg::Utilities::Etl::reverse_iterator<IteratorType> postfix_dec_prev = reverse_iterator--;
  CHECK(&*(random_iterator - 1) == &*(reverse_iterator));
  CHECK(&*(random_iterator - 2) == &*(postfix_dec_prev));

  // Operator +=
  reverse_iterator += 2;
  CHECK(&*(random_iterator - 3) == &*(reverse_iterator));

  // Operator -=
  reverse_iterator -= 2;
  CHECK(&*(random_iterator - 1) == &*(reverse_iterator));

  // Operator + (first arg is reverse_iterator)
  Elg::Utilities::Etl::reverse_iterator<IteratorType> add_new_v1 = reverse_iterator + 2;
  CHECK(&*(random_iterator - 1) == &*(reverse_iterator));
  CHECK(&*(random_iterator - 3) == &*(add_new_v1));

  // Operator + (first arg is a number)
  Elg::Utilities::Etl::reverse_iterator<IteratorType> add_new_v2 = 2 + reverse_iterator;
  CHECK(&*(random_iterator - 1) == &*(reverse_iterator));
  CHECK(&*(random_iterator - 3) == &*(add_new_v2));

  // Operator - (reverse iterator and a number)
  Elg::Utilities::Etl::reverse_iterator<IteratorType> sub_new = reverse_iterator - 2;
  CHECK(&*(random_iterator - 1) == &*(reverse_iterator));
  CHECK(&*(random_iterator + 1) == &*(sub_new));

  // Operator - (reverse_iterator difference)
  CHECK_EQUAL(4, add_new_v2 - sub_new);   // (+2) - (-2) =  4
  CHECK_EQUAL(-4, sub_new - add_new_v2);  // (-2) - (+2) = -4

  // Operator []
  CHECK(&*(random_iterator - 1) == &(reverse_iterator[0]));
  CHECK(&*(random_iterator - 2) == &(reverse_iterator[1]));
}

TEST(Etl_Iterators_ReverseIterator_Comparison) {
  // Typedefs
  typedef Elg::Utilities::Etl::pair<elg_int32, elg_int32> ValueType;
  typedef ValueType* IteratorType;

  // Helper variables
  typedef Elg::Utilities::Etl::pair<elg_int32, elg_int32> Int32Pair;  // NOLINT(build/include_what_you_use)
  ValueType test_array[] = { Int32Pair(1, -1),
                             Int32Pair(2, -2),
                             Int32Pair(3, -3),
                             Int32Pair(4, -4),
                             Int32Pair(5, -5) };
  IteratorType random_iterator = test_array + 3;

  // Construct the iterator
  Elg::Utilities::Etl::reverse_iterator<IteratorType> reverse_iterator(random_iterator);
  const Elg::Utilities::Etl::reverse_iterator<IteratorType> const_reverse_iterator(random_iterator);

  // Check - equal
  CHECK(reverse_iterator == const_reverse_iterator);
  CHECK(!(reverse_iterator != const_reverse_iterator));
  CHECK(!(reverse_iterator <  const_reverse_iterator));
  CHECK(reverse_iterator <= const_reverse_iterator);
  CHECK(!(reverse_iterator >  const_reverse_iterator));
  CHECK(reverse_iterator >= const_reverse_iterator);

  // Move the reverse_iterator up
  ++reverse_iterator;

  // Check - greater
  CHECK(!(reverse_iterator == const_reverse_iterator));
  CHECK(reverse_iterator != const_reverse_iterator);
  CHECK(!(reverse_iterator <  const_reverse_iterator));
  CHECK(!(reverse_iterator <= const_reverse_iterator));
  CHECK(reverse_iterator >  const_reverse_iterator);
  CHECK(reverse_iterator >= const_reverse_iterator);

  // Move the reverse_iterator down by 2
  reverse_iterator -= 2;

  // Check - smaller
  CHECK(!(reverse_iterator == const_reverse_iterator));
  CHECK(reverse_iterator != const_reverse_iterator);
  CHECK(reverse_iterator <  const_reverse_iterator);
  CHECK(reverse_iterator <= const_reverse_iterator);
  CHECK(!(reverse_iterator >  const_reverse_iterator));
  CHECK(!(reverse_iterator >= const_reverse_iterator));
}

TEST(Etl_Iterators_BackInsertIterator) {
  // Setup a fake container
  DummyContainer<elg_int32> container;

  // Create the iterator
  Elg::Utilities::Etl::back_insert_iterator<DummyContainer<elg_int32>> back_insert_iterator(container);

  // Test the iterator - operator =
  back_insert_iterator = 1;
  CHECK_EQUAL(1, container.Value);
  CHECK_EQUAL(DummyContainer<elg_int32>::LAST_ACTION_PUSH_BACK, container.Action);
  CHECK_EQUAL(static_cast<elg_int32*>(NULL), container.InsertionPoint);

  // Test the iterator - operator *
  CHECK(&back_insert_iterator == &(*back_insert_iterator));

  // operator++ is pretty much untestable
}

TEST(Etl_Iterators_FrontInsertIterator) {
  // Setup a fake container
  DummyContainer<elg_int32> container;

  // Create the iterator
  Elg::Utilities::Etl::front_insert_iterator<DummyContainer<elg_int32>> front_insert_iterator(container);

  // Test the iterator - operator =
  front_insert_iterator = 1;
  CHECK_EQUAL(1, container.Value);
  CHECK_EQUAL(DummyContainer<elg_int32>::LAST_ACTION_PUSH_FRONT, container.Action);
  CHECK_EQUAL(static_cast<elg_int32*>(NULL), container.InsertionPoint);

  // Test the iterator - operator *
  CHECK(&front_insert_iterator == &(*front_insert_iterator));

  // operator++ is pretty much untestable
}

TEST(Etl_Iterators_InsertIterator) {
  // Setup a fake container
  DummyContainer<elg_int32> container;

  // Create the iterator
  DummyContainer<elg_int32>::iterator it = container.begin();
  Elg::Utilities::Etl::insert_iterator<DummyContainer<elg_int32>> insert_iterator(container, it);

  // Test the iterator - operator =
  insert_iterator = 1;
  CHECK_EQUAL(1, container.Value);
  CHECK_EQUAL(DummyContainer<elg_int32>::LAST_ACTION_INSERT, container.Action);
  CHECK(it == container.InsertionPoint);

  // Test the iterator - operator *
  CHECK(&insert_iterator == &(*insert_iterator));

  // operator++ is pretty much untestable and so is operator=
}

TEST(Etl_Iterators_Distance) {
  // Helper variables
  elg_int32 test_array[] = {1, 2, 3, 4, 5};

  // Create random access iterators and test
  TestRandomIterator random_start_iterator(test_array);
  TestRandomIterator random_end_iterator(test_array + 4);
  CHECK_EQUAL(4, Elg::Utilities::Etl::distance(random_start_iterator, random_end_iterator));

  // Create input iterators and test
  TestInputIterator input_start_iterator(test_array);
  TestInputIterator input_end_iterator(test_array + 4);
  CHECK_EQUAL(4, Elg::Utilities::Etl::distance(input_start_iterator, input_end_iterator));
}

TEST(Etl_Iterators_Advance) {
  // Helper variables
  elg_int32 test_array[] = {1, 2, 3, 4, 5};

  // Create random access iterators and test
  TestRandomIterator random_iterator(test_array);
  Elg::Utilities::Etl::advance(random_iterator, 4);
  CHECK((test_array + 4) == random_iterator.base());
  Elg::Utilities::Etl::advance(random_iterator, -2);
  CHECK((test_array + 2) == random_iterator.base());

  // Create bidirectional iterators and test
  TestBidirectionalIterator bidirectional_iterator(test_array);
  Elg::Utilities::Etl::advance(bidirectional_iterator, 4);
  CHECK((test_array + 4) == bidirectional_iterator.base());
  Elg::Utilities::Etl::advance(bidirectional_iterator, -2);
  CHECK((test_array + 2) == bidirectional_iterator.base());

  // Create input iterators and test
  TestInputIterator input_iterator(test_array);
  Elg::Utilities::Etl::advance(input_iterator, 4);
  CHECK((test_array + 4) == input_iterator.base());
}

