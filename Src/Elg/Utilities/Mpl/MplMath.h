/*
 * Copyright (c) 2012 Bartlomiej Siwek All rights reserved.
 */

#ifndef ELG_UTILITIES_MPL_MPLMATH_H_
#define ELG_UTILITIES_MPL_MPLMATH_H_

#include "Elg/Utilities/Types.h"
#include "Elg/Utilities/Asserts.h"

namespace Elg {
namespace Utilities {
namespace Mpl {

// Sign
template<elg_int64 Value>
struct Sign {
  static const elg_int64 value = (Value < 0) ? (-1) : (Value > 0 ? 1 : 0);
};

// Abs
template<elg_int64 Value>
struct Abs {
  static const elg_int64 value = Value * Sign<Value>::value;
};

// Multiply - uses http://www.fefe.de/intof.html
template<elg_int64 Lhs, elg_int64 Rhs>
struct Multiply {
 private:
  static const elg_uint64 MAX = static_cast<elg_uint64>(0x7fffffffffffffff);

  static const elg_uint64 c = static_cast<elg_uint64>(1) << 32;  // Half of 64

  static const elg_uint64 LhsLow = Abs<Lhs>::value % c;
  static const elg_uint64 LhsHigh = Abs<Lhs>::value / c;
  static const elg_uint64 RhsLow = Abs<Rhs>::value % c;
  static const elg_uint64 RhsHigh = Abs<Rhs>::value / c;

  static const elg_uint64 a = LhsLow * RhsHigh + RhsLow * LhsHigh;

  STATIC_ASSERT(LhsHigh == 0 || RhsHigh == 0, "Overflow in MPL Multiply");
  STATIC_ASSERT(a < (c >> 1), "Overflow in MPL Multiply");  // Account for the sign bit
  STATIC_ASSERT(RhsLow * LhsLow <= MAX, "Overflow in MPL Multiply");  // This is just to be safe
  STATIC_ASSERT(a * c <= MAX -  RhsLow * LhsLow, "Overflow in MPL Multiply");

 public:
  static const elg_int64 value = Lhs * Rhs;
};

// Add
template<elg_int64 Lhs, elg_int64 Rhs, bool>
struct AddCheckedImplementation;

template<elg_int64 Lhs, elg_int64 Rhs>
struct AddCheckedImplementation<Lhs, Rhs, true> {
  static const elg_int64 MAX = static_cast<elg_int64>(0x7fffffffffffffff);

  enum { value = (Lhs <= MAX - Rhs) };
};

template<elg_int64 Lhs, elg_int64 Rhs>
struct AddCheckedImplementation<Lhs, Rhs, false> {
  static const elg_int64 MIN = -static_cast<elg_int64>(0x8000000000000000);

  enum { value = (Lhs >= MIN - Rhs) };
};

template<elg_int64 Lhs, elg_int64 Rhs>
struct AddChecked : AddCheckedImplementation<Lhs, Rhs, (Rhs >= 0)> {
};

template<elg_int64 Lhs, elg_int64 Rhs>
struct Add {
  static_assert(AddChecked<Lhs, Rhs>::value != 0, "Overflow in Add");

  static const elg_int64 value = Lhs + Rhs;
};

// Min-Max
template<elg_int64 X, elg_int64 Y>
struct Min {
  static const elg_int64 value = (X > Y ? Y : X);
};

template<elg_int64 X, elg_int64 Y>
struct Max {
  static const elg_int64 value = (X > Y ? X : Y);
};

// Log2
template<elg_uint64 Value>
struct Log2 {
  static const elg_uint64 value = 1 + Log2<Value / 2>::value;
};

template<>
struct Log2<0> {
  static const elg_uint64 value = 0;
};

template<>
struct Log2<1> {
  static const elg_uint64 value = 0;
};

// IsPow2
template<elg_int64 Value, bool Positive>
struct IsPow2Implementation;

template<elg_int64 Value>
struct IsPow2Implementation<Value, true> {
  static const bool value = !(Value & (Value-1));
};

template<elg_int64 Value>
struct IsPow2Implementation<Value, false> {
  static const bool value = !((-Value) & ((-Value)-1));
};

template<elg_int64 Value>
struct IsPow2 {
  static const bool value = IsPow2Implementation<Value, (Value > 0)>::value;
};

// Pow2
template<elg_uint64 Exponent>
struct Pow2 {
  STATIC_ASSERT(Exponent < 64, "The exponent must be less than 64");
  static const elg_uint64 value = (static_cast<elg_uint64>(1) << Exponent);
};

}  // namespace Mpl
}  // namespace Utilities
}  // namespace Elg

#endif  // ELG_UTILITIES_MPL_MPLMATH_H_
