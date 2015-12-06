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

#ifndef ELG_UTILITIES_ETL_FUNCTIONAL_H_
#define ELG_UTILITIES_ETL_FUNCTIONAL_H_

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/ETL/TypeTraits.h"

namespace Elg {
namespace Utilities {
namespace Etl {

// Primary C++ functions
template<typename Argument, typename Result>
struct unary_function {
  typedef Argument argument_type;
  typedef Result   result_type;
};

template<typename Argument1, typename Argument2, typename Result>
struct binary_function {
  typedef Argument1 first_argument_type;
  typedef Argument2 second_argument_type;
  typedef Result    result_type;
};

template<typename T>
struct plus : public binary_function<T, T, T> {
  T operator()(const T& a, const T& b) const {
    return a + b;
  }
};

template<typename T>
struct minus : public binary_function<T, T, T> {
  T operator()(const T& a, const T& b) const {
    return a - b;
  }
};

template<typename T>
struct multiplies : public binary_function<T, T, T> {
  T operator()(const T& a, const T& b) const {
    return a * b;
  }
};

template<typename T>
struct divides : public binary_function<T, T, T> {
  T operator()(const T& a, const T& b) const {
    return a / b;
  }
};

template<typename T>
struct modulus : public binary_function<T, T, T> {
  T operator()(const T& a, const T& b) const {
    return a % b;
  }
};

template<typename T>
struct negate : public unary_function<T, T> {
  T operator()(const T& a) const {
    return -a;
  }
};

template<typename T>
struct equal_to : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a == b;
  }
};

template<typename T, typename Compare>
bool validate_equal_to(const T& a, const T& b, Compare compare) {
  return compare(a, b) == compare(b, a);
}

template<typename T>
struct not_equal_to : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a != b;
  }
};

template<typename T, typename Compare>
bool validate_not_equal_to(const T& a, const T& b, Compare compare) {
  return compare(a, b) == compare(b, a);  // We want the not equal comparison results to be equal.
}

// str_equal_to
//   Compares two 0-terminated string types. The T types are expected to be iterators or act like iterators.
//
//   Example usage:
//     hash_set<const char*, hash<const char*>, str_equal_to<const char*> > stringHashSet;
//
//   Note:
//     You couldn't use str_equal_to like this:
//       bool result = equal("hi", "hi" + 2, "ho", str_equal_to<const char*>());
//     This is because equal tests an array of something, with each element by the comparison function. But
//     str_equal_to tests an array of something itself.
template<typename T>
struct str_equal_to : public binary_function<T, T, bool> {
  bool operator()(T a, T b) const {
    while (*a && (*a == *b)) {
      ++a;
      ++b;
    }
    return (*a == *b);
  }
};

template<typename T>
struct greater : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a > b;
  }
};

template<typename T, typename Compare>
bool validate_greater(const T& a, const T& b, Compare compare) {
  return !compare(a, b) || !compare(b, a);  // If (a > b), then !(b > a)
}

template<typename T>
struct less : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a < b;
  }
};

template<typename T, typename Compare>
bool validate_less(const T& a, const T& b, Compare compare) {
  return !compare(a, b) || !compare(b, a);  // If (a < b), then !(b < a)
}

template<typename T>
struct greater_equal : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a >= b;
  }
};

template<typename T, typename Compare>
bool validate_greater_equal(const T& a, const T& b, Compare compare) {
  return !compare(a, b) || !compare(b, a);  // If (a >= b), then !(b >= a)
}

template<typename T>
struct less_equal : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a <= b;
  }
};

template<typename T, typename Compare>
bool validate_less_equal(const T& a, const T& b, Compare compare) {
  return !compare(a, b) || !compare(b, a);  // If (a <= b), then !(b <= a)
}

template<typename T>
struct logical_and : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a && b;
  }
};

template<typename T>
struct logical_or : public binary_function<T, T, bool> {
  bool operator()(const T& a, const T& b) const {
    return a || b;
  }
};

template<typename T>
struct logical_not : public unary_function<T, bool> {
  bool operator()(const T& a) const {
    return !a;
  }
};

// Dual type functions
template<typename T, typename U>
struct equal_to_2 : public binary_function<T, U, bool> {
  bool operator()(const T& a, const U& b) const {
    return a == b;
  }
};

template<typename T, typename U>
struct not_equal_to_2 : public binary_function<T, U, bool> {
  bool operator()(const T& a, const U& b) const {
    return a != b;
  }
};

template<typename T, typename U>
struct less_2 : public binary_function<T, U, bool> {
  bool operator()(const T& a, const U& b) const {
    return a < b;
  }
};

// unary_negate
template<typename Predicate>
class unary_negate : public unary_function<typename Predicate::argument_type, bool> {
 public:
  explicit unary_negate(const Predicate& a)
      : m_predicate_(a) {
  }

  bool operator()(const typename Predicate::argument_type& a) const {
    return !m_predicate_(a);
  }

 protected:
  Predicate m_predicate_;
};

template<typename Predicate>
inline unary_negate<Predicate> not1(const Predicate& predicate) {
  return unary_negate<Predicate>(predicate);
}

// binary_negate
template<typename Predicate>
class binary_negate : public binary_function<typename Predicate::first_argument_type,
                                             typename Predicate::second_argument_type, bool> {
 public:
  explicit binary_negate(const Predicate& a)
      : m_predicate_(a) {
  }

  bool operator()(const typename Predicate::first_argument_type& a,
                  const typename Predicate::second_argument_type& b) const {
    return !m_predicate_(a, b);
  }

 protected:
  Predicate m_predicate_;
};

template<typename Predicate>
inline binary_negate<Predicate> not2(const Predicate& predicate) {
  return binary_negate<Predicate>(predicate);
}

// bind1st
template<typename Operation>
class binder1st : public unary_function<typename Operation::second_argument_type, typename Operation::result_type> {
 public:
  binder1st(const Operation& x, const typename Operation::first_argument_type& y)
      : m_value_(y), m_op_(x) {
  }

  typename Operation::result_type operator()(const typename Operation::second_argument_type& x) const {
    return m_op_(m_value_, x);
  }

  typename Operation::result_type operator()(
      typename Operation::second_argument_type& x) const {  // NOLINT(runtime/references)
    return m_op_(m_value_, x);
  }

 protected:
  typename Operation::first_argument_type m_value_;
  Operation m_op_;
};

template<typename Operation, typename T>
inline binder1st<Operation> bind1st(const Operation& op, const T& x) {
  typedef typename Operation::first_argument_type value;
  return binder1st<Operation>(op, value(x));
}

// bind2nd
template<typename Operation>
class binder2nd : public unary_function<typename Operation::first_argument_type, typename Operation::result_type> {
 public:
  binder2nd(const Operation& x, const typename Operation::second_argument_type& y)
      : m_op_(x), m_value_(y) {
  }

  typename Operation::result_type operator()(const typename Operation::first_argument_type& x) const {
    return m_op_(x, m_value_);
  }

  typename Operation::result_type operator()(
      typename Operation::first_argument_type& x) const {  // NOLINT(runtime/references)
    return m_op_(x, m_value_);
  }

 protected:
  Operation m_op_;
  typename Operation::second_argument_type m_value_;
};

template<typename Operation, typename T>
inline binder2nd<Operation> bind2nd(const Operation& op, const T& x) {
  typedef typename Operation::second_argument_type value;
  return binder2nd<Operation>(op, value(x));
}

// pointer_to_unary_function
//   This is an adapter template which converts a pointer to a standalone function to a function object. This allows
//   standalone functions to work in many cases where the system requires a function object.
//
//   Example usage:
//     ptrdiff_t Rand(ptrdiff_t n) { return rand() % n; } // Note: The C rand function is poor and slow.
//     pointer_to_unary_function<ptrdiff_t, ptrdiff_t> randInstance(Rand);
//     random_shuffle(pArrayBegin, pArrayEnd, randInstance);
template<typename Arg, typename Result>
class pointer_to_unary_function : public unary_function<Arg, Result> {
 public:
  pointer_to_unary_function() {
  }

  explicit pointer_to_unary_function(Result (*pFunction)(Arg))
      : m_function_(pFunction) {
  }

  Result operator()(Arg x) const {
    return m_function_(x);
  }

 protected:
  Result (*m_function_)(Arg);
};

// ptr_fun
//   This ptr_fun is simply shorthand for usage of pointer_to_unary_function.
//
//   Example usage (actually, you don't need to use ptr_fun here, but it works anyway):
//     int factorial(int x) { return (x > 1) ? (x * factorial(x - 1)) : x; }
//     transform(pIntArrayBegin, pIntArrayEnd, pIntArrayBegin, ptr_fun(factorial));
template<typename Arg, typename Result>
inline pointer_to_unary_function<Arg, Result> ptr_fun(Result (*pFunction)(Arg)) {
  return pointer_to_unary_function<Arg, Result>(pFunction);
}

// pointer_to_binary_function
//   This is an adapter template which converts a pointer to a standalone function to a function object. This allows
//   standalone functions to work in many cases where the system requires a function object.
template<typename Arg1, typename Arg2, typename Result>
class pointer_to_binary_function : public binary_function<Arg1, Arg2, Result> {
 public:
  pointer_to_binary_function() {
  }

  explicit pointer_to_binary_function(Result (*pFunction)(Arg1, Arg2))
      : m_function_(pFunction) {
  }

  Result operator()(Arg1 x, Arg2 y) const {
    return m_function_(x, y);
  }

 protected:
  Result (*m_function_)(Arg1, Arg2);
};

// This ptr_fun is simply shorthand for usage of pointer_to_binary_function.
//   Example usage (actually, you don't need to use ptr_fun here, but it works anyway):
//     int multiply(int x, int y) { return x * y; }
//     transform(pIntArray1Begin, pIntArray1End, pIntArray2Begin, pIntArray1Begin, ptr_fun(multiply));
template<typename Arg1, typename Arg2, typename Result>
inline pointer_to_binary_function<Arg1, Arg2, Result> ptr_fun(Result (*pFunction)(Arg1, Arg2)) {
  return pointer_to_binary_function<Arg1, Arg2, Result>(pFunction);
}

// mem_fun
// mem_fun1
//   Note that mem_fun calls member functions via *pointers* to classes and not instances of classes. mem_fun_ref is
//   for calling functions via instances of classes or references to classes.

// mem_fun_t
//   Member function with no arguments.
template<typename Result, typename T>
class mem_fun_t : public unary_function<T*, Result> {
 public:
  typedef Result (T::*MemberFunction)();

  ELG_FORCEINLINE explicit mem_fun_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(T* pT) const {
    return (pT->*m_member_function_)();
  }

 protected:
  MemberFunction m_member_function_;
};

// mem_fun1_t
//   Member function with one argument.
template<typename Result, typename T, typename Argument>
class mem_fun1_t : public binary_function<T*, Argument, Result> {
 public:
  typedef Result (T::*MemberFunction)(Argument);

  ELG_FORCEINLINE explicit mem_fun1_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(T* pT, Argument arg) const {
    return (pT->*m_member_function_)(arg);
  }

 protected:
  MemberFunction m_member_function_;
};


// const_mem_fun_t
//   Const member function with no arguments. Note that we inherit from unary_function<const T*, Result> instead of
//   what the C++ standard specifies: unary_function<T*, Result>. The C++ standard is in error and this has been
//   recognized by the defect group.
template<typename Result, typename T>
class const_mem_fun_t : public unary_function<const T*, Result> {
 public:
  typedef Result (T::*MemberFunction)() const;

  ELG_FORCEINLINE explicit const_mem_fun_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(const T* pT) const {
    return (pT->*m_member_function_)();
  }

 protected:
  MemberFunction m_member_function_;
};

// const_mem_fun1_t
//   Const member function with one argument. Note that we inherit from unary_function<const T*, Result> instead of
//   what the C++ standard specifies: unary_function<T*, Result>. The C++ standard is in error and this has been
//   recognized by the defect group.
template<typename Result, typename T, typename Argument>
class const_mem_fun1_t : public binary_function<const T*, Argument, Result> {
 public:
  typedef Result (T::*MemberFunction)(Argument) const;

  ELG_FORCEINLINE explicit const_mem_fun1_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(const T* pT, Argument arg) const {
    return (pT->*m_member_function_)(arg);
  }

 protected:
  MemberFunction m_member_function_;
};

// mem_fun
//   This is the high level interface to the mem_fun_t family.
//
//   Example usage:
//     struct TestClass { void print() { puts("hello"); } }
//     TestClass* pTestClassArray[3] = { ... };
//     for_each(pTestClassArray, pTestClassArray + 3, &TestClass::print);
template<typename Result, typename T>
ELG_FORCEINLINE mem_fun_t<Result, T> mem_fun(Result (T::*MemberFunction)()) {
  return Elg::Utilities::Etl::mem_fun_t<Result, T>(MemberFunction);
}

template<typename Result, typename T, typename Argument>
ELG_FORCEINLINE mem_fun1_t<Result, T, Argument> mem_fun(Result (T::*MemberFunction)(Argument)) {
  return Elg::Utilities::Etl::mem_fun1_t<Result, T, Argument>(MemberFunction);
}

template<typename Result, typename T>
ELG_FORCEINLINE const_mem_fun_t<Result, T> mem_fun(Result (T::*MemberFunction)() const) {
  return Elg::Utilities::Etl::const_mem_fun_t<Result, T>(MemberFunction);
}

template<typename Result, typename T, typename Argument>
ELG_FORCEINLINE const_mem_fun1_t<Result, T, Argument> mem_fun(Result (T::*MemberFunction)(Argument) const) {
  return Elg::Utilities::Etl::const_mem_fun1_t<Result, T, Argument>(MemberFunction);
}

// mem_fun_ref_t
template<typename Result, typename T>
class mem_fun_ref_t : public unary_function<T, Result> {
 public:
  typedef Result (T::*MemberFunction)();

  ELG_FORCEINLINE explicit mem_fun_ref_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(T& t) const {  // NOLINT(runtime/references)
    return (t.*m_member_function_)();
  }

 protected:
  MemberFunction m_member_function_;
};

// mem_fun1_ref_t
template<typename Result, typename T, typename Argument>
class mem_fun1_ref_t : public binary_function<T, Argument, Result> {
 public:
  typedef Result (T::*MemberFunction)(Argument);

  ELG_FORCEINLINE explicit mem_fun1_ref_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(T& t, Argument arg) const {  // NOLINT(runtime/references)
    return (t.*m_member_function_)(arg);
  }

 protected:
  MemberFunction m_member_function_;
};

// const_mem_fun_ref_t
template<typename Result, typename T>
class const_mem_fun_ref_t : public unary_function<T, Result> {
 public:
  typedef Result (T::*MemberFunction)() const;

  ELG_FORCEINLINE explicit const_mem_fun_ref_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(const T& t) const {
    return (t.*m_member_function_)();
  }

 protected:
  MemberFunction m_member_function_;
};

// const_mem_fun1_ref_t
template<typename Result, typename T, typename Argument>
class const_mem_fun1_ref_t : public binary_function<T, Argument, Result> {
 public:
  typedef Result (T::*MemberFunction)(Argument) const;

  ELG_FORCEINLINE explicit const_mem_fun1_ref_t(MemberFunction member_function)
      : m_member_function_(member_function) {
  }

  ELG_FORCEINLINE Result operator()(const T& t, Argument arg) const {
    return (t.*m_member_function_)(arg);
  }

 protected:
  MemberFunction m_member_function_;
};

// mem_fun_ref
//   Example usage:
//     struct TestClass { void print() { puts("hello"); } }
//     TestClass testClassArray[3];
//     for_each(testClassArray, testClassArray + 3, &TestClass::print);
template<typename Result, typename T>
ELG_FORCEINLINE mem_fun_ref_t<Result, T> mem_fun_ref(Result (T::*MemberFunction)()) {
  return Elg::Utilities::Etl::mem_fun_ref_t<Result, T>(MemberFunction);
}

template<typename Result, typename T, typename Argument>
ELG_FORCEINLINE mem_fun1_ref_t<Result, T, Argument> mem_fun_ref(Result (T::*MemberFunction)(Argument)) {
  return Elg::Utilities::Etl::mem_fun1_ref_t<Result, T, Argument>(MemberFunction);
}

template<typename Result, typename T>
ELG_FORCEINLINE const_mem_fun_ref_t<Result, T> mem_fun_ref(Result (T::*MemberFunction)() const) {
  return Elg::Utilities::Etl::const_mem_fun_ref_t<Result, T>(MemberFunction);
}

template<typename Result, typename T, typename Argument>
ELG_FORCEINLINE const_mem_fun1_ref_t<Result, T, Argument> mem_fun_ref(Result (T::*MemberFunction)(Argument) const) {
  typedef Elg::Utilities::Etl::const_mem_fun1_ref_t<Result, T, Argument> RType;  // NOLINT(build/include_what_you_use)
  return RType(MemberFunction);
}

}  // namespace Etl
}  // namespace Utilities
}  // namespace Elg

#endif  // ELG_UTILITIES_ETL_FUNCTIONAL_H_
