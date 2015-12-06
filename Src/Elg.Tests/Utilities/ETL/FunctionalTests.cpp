/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#include <UnitTest++.h>

#include "Elg/Utilities/Macros.h"
#include "Elg/Utilities/Types.h"

#include "Elg/Utilities/ETL/Functional.h"

TEST(Etl_Functional_Plus) {
  Elg::Utilities::Etl::plus<elg_int32> f;
  CHECK_EQUAL(4, f(2, 2));
  CHECK_EQUAL(0, f(2, -2));
  CHECK_EQUAL(0, f(-2, 2));
  CHECK_EQUAL(-4, f(-2, -2));
}

TEST(Etl_Functional_Minus) {
  Elg::Utilities::Etl::minus<elg_int32> f;
  CHECK_EQUAL(0, f(2, 2));
  CHECK_EQUAL(4, f(2, -2));
  CHECK_EQUAL(-4, f(-2, 2));
  CHECK_EQUAL(0, f(-2, -2));
}

TEST(Etl_Functional_Multiplies) {
  Elg::Utilities::Etl::multiplies<elg_int32> f;
  CHECK_EQUAL(6, f(3, 2));
  CHECK_EQUAL(-6, f(3, -2));
  CHECK_EQUAL(-6, f(-3, 2));
  CHECK_EQUAL(6, f(-3, -2));
}

TEST(Etl_Functional_Divides) {
  Elg::Utilities::Etl::divides<elg_int32> f;
  CHECK_EQUAL(4, f(8, 2));
  CHECK_EQUAL(-4, f(8, -2));
  CHECK_EQUAL(-4, f(-8, 2));
  CHECK_EQUAL(4, f(-8, -2));
}

TEST(Etl_Functional_Modulus) {
  Elg::Utilities::Etl::modulus<elg_int32> f;
  CHECK_EQUAL(1, f(10, 3));
  CHECK_EQUAL(1, f(10, -3));
  CHECK_EQUAL(-1, f(-10, 3));
  CHECK_EQUAL(-1, f(-10, -3));
}

TEST(Etl_Functional_Negate) {
  Elg::Utilities::Etl::negate<elg_int32> f;
  CHECK_EQUAL(-2, f(2));
  CHECK_EQUAL(2, f(-2));
}

TEST(Etl_Functional_EqualTo) {
  Elg::Utilities::Etl::equal_to<elg_int32> f;
  CHECK_EQUAL(true, f(1, 1));
  CHECK_EQUAL(false, f(2, 1));
  CHECK_EQUAL(false, f(1, 2));
}

TEST(Etl_Functional_ValidateEqualTo) {
  // Helper structs
  struct SaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a - b == 0;
    }
  };

  struct NotSaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a - (b > 0 ? b : -b) == 0;
    }
  };

  // Test
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_equal_to(2, -2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_equal_to(2, -2, NotSaneComparison()));
}

TEST(Etl_Functional_NotEqualTo) {
  Elg::Utilities::Etl::not_equal_to<elg_int32> f;
  CHECK_EQUAL(false, f(1, 1));
  CHECK_EQUAL(true, f(2, 1));
  CHECK_EQUAL(true, f(1, 2));
}

TEST(Etl_Functional_ValidateNotEqualTo) {
  // Helper structs
  struct SaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a - b == 0;
    }
  };

  struct NotSaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a - (b > 0 ? b : -b) == 0;
    }
  };

  // Test
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_not_equal_to(2, -2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_not_equal_to(2, -2, NotSaneComparison()));
}

TEST(Etl_Functional_StrEqualTo) {
  // Helper vars
  char* hi = "hi";
  char* ho = "ho";
  char* hihi = "hihi";
  char* hiho = "hiho";

  // Test
  Elg::Utilities::Etl::str_equal_to<char*> f;
  CHECK_EQUAL(true, f(hi, hi));
  CHECK_EQUAL(false, f(hi, ho));
  CHECK_EQUAL(false, f(ho, hi));
  CHECK_EQUAL(false, f(hihi, hi));
  CHECK_EQUAL(false, f(hi, hihi));
  CHECK_EQUAL(false, f(hiho, hi));
  CHECK_EQUAL(false, f(hi, hiho));
}


TEST(Etl_Functional_Greater) {
  Elg::Utilities::Etl::greater<elg_int32> f;
  CHECK_EQUAL(false, f(1, 1));
  CHECK_EQUAL(true, f(2, 1));
  CHECK_EQUAL(false, f(1, 2));
}

TEST(Etl_Functional_ValidateGreater) {
  // Helper structs
  struct SaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a < b;
    }
  };

  struct NotSaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a < (b > 0 ? b : -b);
    }
  };

  // Test
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_greater(-3, 2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_greater(-3, 2, NotSaneComparison()));
}

TEST(Etl_Functional_Less) {
  Elg::Utilities::Etl::less<elg_int32> f;
  CHECK_EQUAL(false, f(1, 1));
  CHECK_EQUAL(false, f(2, 1));
  CHECK_EQUAL(true, f(1, 2));
}

TEST(Etl_Functional_ValidateLess) {
  // Helper structs
  struct SaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a < b;
    }
  };

  struct NotSaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a < (b > 0 ? b : -b);
    }
  };

  // Test
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_less(-3, 2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_less(-3, 2, NotSaneComparison()));
}

TEST(Etl_Functional_GreaterEqual) {
  Elg::Utilities::Etl::greater_equal<elg_int32> f;
  CHECK_EQUAL(true, f(1, 1));
  CHECK_EQUAL(true, f(2, 1));
  CHECK_EQUAL(false, f(1, 2));
}

TEST(Etl_Functional_ValidateGreaterEqual) {
  // Helper structs
  struct SaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a <= b;
    }
  };

  struct NotSaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a <= (b > 0 ? b : -b);
    }
  };

  // Test
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_greater_equal(2, -2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_greater_equal(2, -2, NotSaneComparison()));
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_greater_equal(-3, 2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_greater_equal(-3, 2, NotSaneComparison()));
}

TEST(Etl_Functional_Less_Equal) {
  Elg::Utilities::Etl::less_equal<elg_int32> f;
  CHECK_EQUAL(true, f(1, 1));
  CHECK_EQUAL(false, f(2, 1));
  CHECK_EQUAL(true, f(1, 2));
}

TEST(Etl_Functional_ValidateLessEqual) {
  // Helper structs
  struct SaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a <= b;
    }
  };

  struct NotSaneComparison {
    bool operator()(elg_int32 a, elg_int32 b) {
      return a <= (b > 0 ? b : -b);
    }
  };

  // Test
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_less_equal(2, -2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_less_equal(2, -2, NotSaneComparison()));
  CHECK_EQUAL(true, Elg::Utilities::Etl::validate_less_equal(-3, 2, SaneComparison()));
  CHECK_EQUAL(false, Elg::Utilities::Etl::validate_less_equal(-3, 2, NotSaneComparison()));
}


TEST(Etl_Functional_LogicalAnd) {
  Elg::Utilities::Etl::logical_and<elg_int32> f;
  CHECK_EQUAL(false, f(0, 0));
  CHECK_EQUAL(false, f(0, 1));
  CHECK_EQUAL(false, f(1, 0));
  CHECK_EQUAL(true, f(1, 1));
}

TEST(Etl_Functional_LogicalOr) {
  Elg::Utilities::Etl::logical_or<elg_int32> f;
  CHECK_EQUAL(false, f(0, 0));
  CHECK_EQUAL(true, f(0, 1));
  CHECK_EQUAL(true, f(1, 0));
  CHECK_EQUAL(true, f(1, 1));
}

TEST(Etl_Functional_LogicalNot) {
  Elg::Utilities::Etl::logical_not<elg_int32> f;
  CHECK_EQUAL(true, f(0));
  CHECK_EQUAL(false, f(1));
}

TEST(Etl_Functional_EqualTo2) {
  Elg::Utilities::Etl::equal_to_2<elg_int32, elg_int16> f;
  CHECK_EQUAL(true, f(1, 1));
  CHECK_EQUAL(false, f(2, 1));
  CHECK_EQUAL(false, f(1, 2));
}

TEST(Etl_Functional_NotEqualTo2) {
  Elg::Utilities::Etl::not_equal_to_2<elg_int32, elg_int16> f;
  CHECK_EQUAL(false, f(1, 1));
  CHECK_EQUAL(true, f(2, 1));
  CHECK_EQUAL(true, f(1, 2));
}

TEST(Etl_Functional_Less2) {
  Elg::Utilities::Etl::less_2<elg_int32, elg_int16> f;
  CHECK_EQUAL(false, f(1, 1));
  CHECK_EQUAL(false, f(2, 1));
  CHECK_EQUAL(true, f(1, 2));
}


TEST(Etl_Functional_UnaryNegate) {
  // Helper structs
  struct Predicate : public Elg::Utilities::Etl::unary_function<elg_int32, elg_int32> {
    elg_int32 operator()(const elg_int32& arg) const {
      return arg - 2;
    }
  };

  Elg::Utilities::Etl::unary_negate<Predicate> negated = Elg::Utilities::Etl::not1(Predicate());

  CHECK_EQUAL(true, negated(2));
  CHECK_EQUAL(false, negated(0));
  CHECK_EQUAL(false, negated(-2));
}

TEST(Etl_Functional_BinaryNegate) {
  // Helper structs
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, elg_int32> {
    elg_int32 operator()(const elg_int32& arg1, const elg_int32& arg2) const {
      return arg1 - arg2;
    }
  };

  Elg::Utilities::Etl::binary_negate<Predicate> negated = Elg::Utilities::Etl::not2(Predicate());

  CHECK_EQUAL(true, negated(2, 2));
  CHECK_EQUAL(false, negated(2, -2));
  CHECK_EQUAL(false, negated(-2, 2));
}

TEST(Etl_Functional_Bind1st) {
  // Helper structs
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, elg_int32> {
    elg_int32 operator()(const elg_int32& arg1, const elg_int32& arg2) const {
      return arg1 - arg2;
    }
  };

  Elg::Utilities::Etl::binder1st<Predicate> bound = Elg::Utilities::Etl::bind1st(Predicate(), 2);

  CHECK_EQUAL(0, bound(2));
  CHECK_EQUAL(2, bound(0));
  CHECK_EQUAL(4, bound(-2));
}

TEST(Etl_Functional_Bind2nd) {
  // Helper structs
  struct Predicate : public Elg::Utilities::Etl::binary_function<elg_int32, elg_int32, elg_int32> {
    elg_int32 operator()(const elg_int32& arg1, const elg_int32& arg2) const {
      return arg1 - arg2;
    }
  };

  Elg::Utilities::Etl::binder2nd<Predicate> bound = Elg::Utilities::Etl::bind2nd(Predicate(), 2);

  CHECK_EQUAL(0, bound(2));
  CHECK_EQUAL(-2, bound(0));
  CHECK_EQUAL(-4, bound(-2));
}

TEST(Etl_Functional_PtrFun) {
  // Helper structs
  struct FunctionWrapper {
    static elg_int32 Function(elg_int32 arg) {
      return arg - 2;
    }
  };

  Elg::Utilities::Etl::pointer_to_unary_function<elg_int32, elg_int32> fun_object =
    Elg::Utilities::Etl::ptr_fun(FunctionWrapper::Function);

  CHECK_EQUAL(0, fun_object(2));
  CHECK_EQUAL(-2, fun_object(0));
}

TEST(Etl_Functional_PtrFunBinary) {
  // Helper structs
  struct FunctionWrapper {
    static elg_int32 Function(elg_int32 arg1, elg_int32 arg2) {
      return arg1 - arg2;
    }
  };

  Elg::Utilities::Etl::pointer_to_binary_function<elg_int32, elg_int32, elg_int32> fun_object =
    Elg::Utilities::Etl::ptr_fun(FunctionWrapper::Function);

  CHECK_EQUAL(0, fun_object(2, 2));
  CHECK_EQUAL(4, fun_object(2, -2));
  CHECK_EQUAL(-4, fun_object(-2, 2));
  CHECK_EQUAL(0, fun_object(-2, -2));
}

TEST(Etl_Functional_MemFun) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function() {
      return X;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::mem_fun_t<elg_int32, FunctionWrapper> fun_object =
    Elg::Utilities::Etl::mem_fun(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(123, fun_object(&wrapper));
}

TEST(Etl_Functional_MemFun1) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function(elg_int32 arg) {
      return X + arg;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::mem_fun1_t<elg_int32, FunctionWrapper, elg_int32> fun_object =
    Elg::Utilities::Etl::mem_fun(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(23, fun_object(&wrapper, -100));
}

TEST(Etl_Functional_ConstMemFun) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function() const {
      return X;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::const_mem_fun_t<elg_int32, FunctionWrapper> fun_object =
    Elg::Utilities::Etl::mem_fun(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(123, fun_object(&wrapper));
}

TEST(Etl_Functional_ConstMemFun1) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function(elg_int32 arg) const {
      return X + arg;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::const_mem_fun1_t<elg_int32, FunctionWrapper, elg_int32> fun_object =
    Elg::Utilities::Etl::mem_fun(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(23, fun_object(&wrapper, -100));
}

TEST(Etl_Functional_MemFunRef) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function() {
      return X;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::mem_fun_ref_t<elg_int32, FunctionWrapper> fun_object =
    Elg::Utilities::Etl::mem_fun_ref(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(123, fun_object(wrapper));
}

TEST(Etl_Functional_MemFun1Ref) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function(elg_int32 arg) {
      return X + arg;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::mem_fun1_ref_t<elg_int32, FunctionWrapper, elg_int32> fun_object =
    Elg::Utilities::Etl::mem_fun_ref(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(23, fun_object(wrapper, -100));
}

TEST(Etl_Functional_ConstMemFunRef) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function() const {
      return X;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::const_mem_fun_ref_t<elg_int32, FunctionWrapper> fun_object =
    Elg::Utilities::Etl::mem_fun_ref(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(123, fun_object(wrapper));
}

TEST(Etl_Functional_ConstMemFun1Ref) {
  // Helper structs
  struct FunctionWrapper {
    explicit FunctionWrapper(elg_int32 x) : X(x) {
    }

    elg_int32 Function(elg_int32 arg) const {
      return X + arg;
    }

    elg_int32 X;
  };

  Elg::Utilities::Etl::const_mem_fun1_ref_t<elg_int32,  // NOLINT(build/include_what_you_use)
                                            FunctionWrapper,
                                            elg_int32>
    fun_object = Elg::Utilities::Etl::mem_fun_ref(&FunctionWrapper::Function);
  FunctionWrapper wrapper(123);

  CHECK_EQUAL(23, fun_object(wrapper, -100));
}
